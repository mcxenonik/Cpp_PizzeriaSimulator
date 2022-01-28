#include "Customer.h"

Customer::Customer(int new_id, std::string new_name, int new_groupID):
Person(new_id, new_name)
{
    groupID = new_groupID;
    state = CustomerStates::NEW;
    eatTime = 0;
    waitingTimeStat = 0;
}

CustomerStates Customer::getState()
{
    return state;
}

int Customer::getGroupID()
{
    return groupID;
}

int Customer::getTableID()
{
    return tableID;
}

int Customer::getOrderID()
{
    return orderID;
}

int Customer::getEatTime()
{
    return eatTime;
}

int Customer::getWaitingTimeState()
{
    return waitingTimeStat;
}

void Customer::setTableID(int new_tableID)
{
    tableID = new_tableID;
}

void Customer::setOrderID(int new_orderID)
{
    orderID = new_orderID;
}

void Customer::setEatTime(int new_eatTime)
{
    eatTime = new_eatTime;
}

void Customer::setState(CustomerStates new_state)
{
    state = new_state;
}

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
            tableID = table_ptr -> getID();
            return true;
        }
    }

    for(auto table_ptr : *tableList_ptr)
    {
        if (table_ptr -> getGroupID() == 0)
        {
            table_ptr -> addCustomerToTable(ID, groupID);
            tableID = table_ptr -> getID();
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
    // int waiterID = findMinTaskWaiter(waiterList_ptr);
    TaskPayload *payload = new TaskPayload();

    Task *new_task = new Task(ID, TaskTypes::GM, payload);

    findMinTaskWaiter(waiterList_ptr) -> addTask(new_task);
    // simulated_pizzeria -> getWaiterByID(waiterID) -> addTask(new_task);

}

void Customer::waitForMenu()
{
    waitingTimeStat++;
}

void Customer::submitOrder(std::vector<Person*>* waiterList_ptr)
{
    // // int waiterID = findMinTaskWaiter();

    // std::vector<Product*> productList = simulated_pizzeria -> getMenu() -> getProductList();

    // std::vector<Product*> orderedProductsList;
    // orderedProductsList.push_back(productList[0]);
    // orderedProductsList.push_back(productList[1]);
    // // std::sample(productList.begin(), productList.end(), std::back_inserter(orderedProductsList), 2, std::mt19937{std::random_device{}()});

    // eatTime = orderedProductsList[0] -> getEatingTime() + orderedProductsList[1] -> getEatingTime();
    
    // TaskPayload *payload = new TaskPayload();
    // payload -> setOrderedProductsList(orderedProductsList);

    // Task *new_task = new Task(ID, TaskTypes::CO, payload);

    // findMinTaskWaiter(waiterList_ptr) -> addTask(new_task);
    // // simulated_pizzeria -> getWaiterByID(waiterID) -> addTask(new_task);

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

void Customer::askForBill(std::vector<Person*>* waiterList_ptr)
{
    // int waiterID = findMinTaskWaiter();

    TaskPayload *payload = new TaskPayload();
    payload -> setOrderID(orderID);

    Task *new_task = new Task(ID, TaskTypes::GR, payload);

    findMinTaskWaiter(waiterList_ptr) -> addTask(new_task);
    // simulated_pizzeria -> getWaiterByID(waiterID) -> addTask(new_task);

}

void Customer::waitForBill()
{
    waitingTimeStat++;
}

void Customer::takeBill(std::vector<Person*>* waiterList_ptr)
{
    // int waiterID = findMinTaskWaiter();

    TaskPayload *payload = new TaskPayload();
    payload -> setOrderID(orderID);

    Task *new_task = new Task(ID, TaskTypes::TR, payload);

    findMinTaskWaiter(waiterList_ptr) -> addTask(new_task);
    // simulated_pizzeria -> getWaiterByID(waiterID) -> addTask(new_task);
}

void Customer::waitForPayBill()
{
    waitingTimeStat++;
}

void Customer::payBill(std::vector<Order*>* orderList_ptr)
{
    (*orderList_ptr)[orderID] -> getReceipt() -> paidReceipt();
    (*orderList_ptr)[orderID] -> setPaid();
    // simulated_pizzeria -> getOrderByID(orderID) -> getReceipt() -> paidReceipt();
    // simulated_pizzeria -> getOrderByID(orderID) -> setPaid();
}

void Customer::out(std::vector<Table*>* tableList_ptr)
{
    (*tableList_ptr)[tableID] -> deleteCustomerFromTable(ID);
    // simulated_pizzeria -> getTableByID(tableID) -> deleteCustomerFromTable(ID);
    tableID = 0;
}

void Customer::doAction(std::vector<Person*>* waiterList_ptr, std::vector<Table*>* tableList_ptr, std::vector<Order*>* orderList_ptr)
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
                state = CustomerStates::AFB;
            }
            else
            {
                printLog(true, 0);
                state = CustomerStates::E;
            }

            break;
        }
        case CustomerStates::AFB:
        {
            askForBill(waiterList_ptr);

            printLog(true, 0);
            state = CustomerStates::WFB;

            break;
        }
        case CustomerStates::WFB:
        {
            waitForBill();

            printLog(true, 0);
            state = CustomerStates::WFB;

            break;
        }
        case CustomerStates::TB:
        {
            takeBill(waiterList_ptr);

            printLog(true, (*orderList_ptr)[orderID] -> getReceipt() -> getTotalPrice());
            state = CustomerStates::WFPB;

            break;
        }
        case CustomerStates::WFPB:
        {
            waitForPayBill();

            printLog(true, 0);
            state = CustomerStates::WFPB;

            break;
        }
        case CustomerStates::PB:
        {
            payBill(orderList_ptr);

            printLog(true, (*orderList_ptr)[orderID] -> getReceipt() -> getTotalPrice());
            state = CustomerStates::OUT;

            break;
        }
        case CustomerStates::OUT:
        {
            out(tableList_ptr);

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
                std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "ZAJMUJE STOLIK:" << tableID << std::endl;
            }
            else
            {
                std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "OCZEKUJE NA WOLNY STOLIK" << std::endl;
            }

            break;
        }
        case CustomerStates::OM:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "ZAMOWIL KARTE DAN" << std::endl;

            break;
        }
        case CustomerStates::WFM:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "OCZEKUJE NA KARTE DAN" << std::endl;

            break;
        }
        case CustomerStates::SO:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << ID << "SKŁADA ZAMOWIENIE" << std::endl;

            break;
        }
        case CustomerStates::WFAO:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "OCZEKUJE NA PRZYJECIE ZAMOWIENIA" << std::endl;

            break;
        }
        case CustomerStates::WFPO:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "OCZEKUJE NA PRZYGOTOWANIE ZAMOWIENIA" << std::endl;

            break;
        }
        case CustomerStates::E:
        {
            if (eatTime != 0)
            {
                std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "SPOZYWA ZAMOWIENIE. POZOSTALO:" << eatTime << std::endl;
            }
            else
            {
                std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "SKONCZYL SPOZYWANIE ZAMOWIENIA" << std::endl;
            }

            break;
        }
        case CustomerStates::AFB:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << ID << "SIEDZACY PRZY STOLIKU:" << tableID << "POPROSIL O RACHUNEK" << std::endl;

            break;
        }
        case CustomerStates::WFB:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "OCZEKUJE NA RACHUNEK" << std::endl;

            break;
        }
        case CustomerStates::TB:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "BIERZE RACHUNEK O WARTOSCI:" << totalPrice << std::endl;

            break;
        }
        case CustomerStates::WFPB:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "OCZEKUJE NA POBRANIE OPLATY" << std::endl;

            break;
        }
        case CustomerStates::PB:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "PLACI RACHUNEK O WARTOSCI:" << totalPrice << std::endl;

            break;
        }
        case CustomerStates::OUT:
        {
            std::cout << "KLIENT:" << ID << "Z GRUPY:" << groupID << "SIEDZACY PRZY STOLIKU:" << tableID << "ODCHODZI" << std::endl;

            break;
        }
    }
}

Customer::~Customer()
{

}


/////////////////////////////////////////////////////////////////////////////////////////////////
int Customer::getNumberOfTasks() { return 0; }

void Customer::addTask(Task* new_task) {}

void Customer::doTask(std::vector<Person*>* newPersonList, std::vector<Order*>* newOrderList) {}
/////////////////////////////////////////////////////////////////////////////////////////////////