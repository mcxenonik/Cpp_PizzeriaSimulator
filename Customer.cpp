#include "Customer.h"

#include "Pizza.h"
#include "Drink.h"

Customer::Customer(int new_id, std::string new_name, int new_groupID):
Person(new_id, new_name)
{
    groupID = new_groupID;
    state = CustomerStates::NEW;
    eatTime = 0;
    waitingTimeStat = 0;
    menu = nullptr;
    order = nullptr;
    table = nullptr;
}

CustomerStates Customer::getState()
{
    return state;
}

int Customer::getWaitingTimeState()
{
    return waitingTimeStat;
}

void Customer::setOrder(Order* new_order)
{
    order = new_order;
}

void Customer::setState(CustomerStates new_state)
{
    state = new_state;
}

void Customer::setMenu(Menu* new_menu)
{
    menu = new_menu;
}

int Customer::getNumberOfTasks() { return 0; }
void Customer::addTask(Task*) {}
void Customer::doTask(std::vector<Person*>*, std::vector<Order*>*) {}

Person* Customer::findMinTaskWaiter(std::vector<Person*>* waiterList_ptr){
    int min_tasks = (*waiterList_ptr)[0] -> getNumberOfTasks();
    int waiterID = (*waiterList_ptr)[0] -> getID();

    for(auto waiter : (*waiterList_ptr)){
        if (waiter -> getNumberOfTasks() < min_tasks){
            min_tasks = waiter -> getNumberOfTasks();
            waiterID = waiter -> getID();
        }
    }
    return (*waiterList_ptr)[waiterID];
}

bool Customer::takeTable(std::vector<Table*>* tableList_ptr)
{
    for(auto table_ptr : *tableList_ptr)
    {
        if (table_ptr -> getGroupID() == groupID && !table_ptr -> getIsFull())
        {
            table_ptr -> addCustomerToTable(ID, groupID);
            table = table_ptr;
            return true;
        }
    }

    for(auto table_ptr : *tableList_ptr)
    {
        if (table_ptr -> getGroupID() == 0)
        {
            table_ptr -> addCustomerToTable(ID, groupID);
            table = table_ptr;
            return true;
        }
    }

    return false;

}

void Customer::waitForFreeTable()
{
    waitingTimeStat++;
}

void Customer::orderMenu(std::vector<Person*>* waiterList_ptr)
{
    TaskPayload *payload = new TaskPayload();

    Task *new_task = new Task(ID, TaskTypes::GM, payload);

    findMinTaskWaiter(waiterList_ptr) -> addTask(new_task);
}

void Customer::waitForMenu()
{
    waitingTimeStat++;
}

void Customer::submitOrder(std::vector<Person*>* waiterList_ptr)
{
    std::vector<Product*> productList = menu -> getProductList();

    std::vector<Product*> orderedProductsList;

    for (int i = 0; i < 2; i++)
    {
        int productId = rand() % productList.size();
        orderedProductsList.push_back(productList[productId]);

        eatTime += productList[productId] -> getEatingTime();
    }

    TaskPayload *payload = new TaskPayload();
    payload -> setOrderedProductsList(orderedProductsList);

    Task *new_task = new Task(ID, TaskTypes::CO, payload);

    findMinTaskWaiter(waiterList_ptr) -> addTask(new_task);
}

void Customer::waitForAcceptOrder()
{
    waitingTimeStat++;
}

void Customer::waitForPrepareOrder()
{
    waitingTimeStat++;
}

void Customer::eat()
{
    eatTime--;
}

void Customer::askForReceipt(std::vector<Person*>* waiterList_ptr)
{
    TaskPayload *payload = new TaskPayload();
    payload -> setOrder(order);

    Task *new_task = new Task(ID, TaskTypes::GR, payload);

    findMinTaskWaiter(waiterList_ptr) -> addTask(new_task);
}

void Customer::waitForReceipt()
{
    waitingTimeStat++;
}

void Customer::takeReceipt(std::vector<Person*>* waiterList_ptr)
{
    TaskPayload *payload = new TaskPayload();
    payload -> setOrder(order);

    Task *new_task = new Task(ID, TaskTypes::TR, payload);

    findMinTaskWaiter(waiterList_ptr) -> addTask(new_task);
}

void Customer::waitForPayReceipt()
{
    waitingTimeStat++;
}

void Customer::payReceipt()
{
    order -> getReceipt() -> paidReceipt();
    order -> setPaid();
}

void Customer::out()
{
    table -> deleteCustomerFromTable(ID);
}

void Customer::doAction(std::vector<Person*>* waiterList_ptr, std::vector<Table*>* tableList_ptr)
{
    switch(state)
    {
        case CustomerStates::NEW:
        {
            bool result = takeTable(tableList_ptr);

            if (result)
            {
                printLog(result, 0);
                state = CustomerStates::OM;
            }
            else
            {
                waitForFreeTable();

                printLog(result, 0);
                state = CustomerStates::NEW;
            }

            break;
        }
        case CustomerStates::OM:
        {
            orderMenu(waiterList_ptr);

            printLog(true, 0);
            state = CustomerStates::WFM;

            break;
        }
        case CustomerStates::WFM:
        {
            waitForMenu();

            printLog(true, 0);
            state = CustomerStates::WFM;

            break;
        }
        case CustomerStates::SO:
        {
            submitOrder(waiterList_ptr);

            printLog(true, 0);
            state = CustomerStates::WFAO;

            break;
        }
        case CustomerStates::WFAO:
        {
            waitForAcceptOrder();

            printLog(true, 0);
            state = CustomerStates::WFAO;

            break;
        }
        case CustomerStates::WFPO:
        {
            waitForPrepareOrder();

            printLog(true, 0);
            state = CustomerStates::WFPO;

            break;
        }
        case CustomerStates::E:
        {
            eat();

            if (eatTime == 0)
            {
                printLog(true, 0);
                state = CustomerStates::AFR;
            }
            else
            {
                printLog(true, 0);
                state = CustomerStates::E;
            }

            break;
        }
        case CustomerStates::AFR:
        {
            askForReceipt(waiterList_ptr);

            printLog(true, 0);
            state = CustomerStates::WFR;

            break;
        }
        case CustomerStates::WFR:
        {
            waitForReceipt();

            printLog(true, 0);
            state = CustomerStates::WFR;

            break;
        }
        case CustomerStates::TR:
        {
            takeReceipt(waiterList_ptr);

            printLog(true, order -> getReceipt() -> getTotalPrice());
            state = CustomerStates::WFPR;

            break;
        }
        case CustomerStates::WFPR:
        {
            waitForPayReceipt();

            printLog(true, 0);
            state = CustomerStates::WFPR;

            break;
        }
        case CustomerStates::PR:
        {
            payReceipt();

            printLog(true, order -> getReceipt() -> getTotalPrice());
            state = CustomerStates::OUT;

            break;
        }
        case CustomerStates::OUT:
        {
            out();

            printLog(true, 0);
            state = CustomerStates::OUT;

            break;
        }
    }

}

void Customer::printLog(bool result, int totalPrice)
{
    switch(state)
    {
        case CustomerStates::NEW:
        {
            if (result)
            {
                std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " ZAJMUJE STOLIK: " << table -> getID() << std::endl;
            }
            else
            {
                std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " OCZEKUJE NA WOLNY STOLIK" << std::endl;
            }

            break;
        }
        case CustomerStates::OM:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " ZAMOWIL KARTE DAN" << std::endl;

            break;
        }
        case CustomerStates::WFM:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " OCZEKUJE NA KARTE DAN" << std::endl;

            break;
        }
        case CustomerStates::SO:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << ID << " SKŁADA ZAMOWIENIE" << std::endl;

            break;
        }
        case CustomerStates::WFAO:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " OCZEKUJE NA PRZYJECIE ZAMOWIENIA" << std::endl;

            break;
        }
        case CustomerStates::WFPO:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " OCZEKUJE NA PRZYGOTOWANIE ZAMOWIENIA" << std::endl;

            break;
        }
        case CustomerStates::E:
        {
            if (eatTime != 0)
            {
                std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " SPOZYWA ZAMOWIENIE. POZOSTALO: " << eatTime << std::endl;
            }
            else
            {
                std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " SKONCZYL SPOZYWANIE ZAMOWIENIA" << std::endl;
            }

            break;
        }
        case CustomerStates::AFR:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << ID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " POPROSIL O RACHUNEK" << std::endl;

            break;
        }
        case CustomerStates::WFR:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY:" << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " OCZEKUJE NA RACHUNEK" << std::endl;

            break;
        }
        case CustomerStates::TR:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " BIERZE RACHUNEK O WARTOSCI: " << totalPrice << std::endl;

            break;
        }
        case CustomerStates::WFPR:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " OCZEKUJE NA POBRANIE OPLATY" << std::endl;

            break;
        }
        case CustomerStates::PR:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " PLACI RACHUNEK O WARTOSCI: " << totalPrice << std::endl;

            break;
        }
        case CustomerStates::OUT:
        {
            std::cout << "KLIENT: " << ID << " Z GRUPY: " << groupID << " SIEDZACY PRZY STOLIKU: " << table -> getID() << " ODCHODZI" << std::endl;

            break;
        }
    }
}

Customer::~Customer()
{

}