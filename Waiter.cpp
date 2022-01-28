#include "Waiter.h"

Waiter::Waiter(int new_id, std::string new_name, Menu* menu):
Person(new_id, new_name)
{
    tasksDoneStat = 0;
    valueOfCollectedOrdersStat = 0;
}

int Waiter::getTasksDoneStat()
{
    return tasksDoneStat;
}

int Waiter::getValueOfCollectedOrdersStat()
{
    return valueOfCollectedOrdersStat;
}

int Waiter::getNumberOfTasks()
{
    return taskQueue.size();
}

void Waiter::addTask(Task *new_task)
{
    taskQueue.push_back(new_task);
}

void Waiter::doTask(std::vector<Person*>* customerList_ptr, std::vector<Order*>* orderList_ptr)
{
    if(taskQueue.size() == 0)
    {
        printLog(TaskTypes::FR, 0, 0);
        return;
    }

    tasksDoneStat += 1;

    Task* task = taskQueue.front();
    taskQueue.erase(taskQueue.begin());

    TaskTypes taskType = task -> getTaskType();
    int customerId = task -> getCustomerID();

    switch(taskType)
    {
        case TaskTypes::GM:
        {
            (*customerList_ptr)[customerId] -> setState(CustomerStates::SO);
            
            (*customerList_ptr)[customerId] -> setMenu(menu);

            printLog(taskType, customerId, 0);
            break;
        }
        case TaskTypes::CO:
        {
            std::vector<Product*> orderedProductsList = task -> getTaskPayload() -> getOrderedProductsList();

            (*customerList_ptr)[customerId] -> setState(CustomerStates::WFPO);

            Order* new_order = new Order((*orderList_ptr).size(), customerId, ID, orderedProductsList);
            (*orderList_ptr).push_back(new_order);
            int orderID = new_order -> getID();

            (*customerList_ptr)[customerId] -> setOrderID(orderID);

            valueOfCollectedOrdersStat += orderedProductsList[0] -> getPrice() + orderedProductsList[1] -> getPrice();

            printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes::DO:
        {
            int orderID = task -> getTaskPayload() -> getOrderID();
            
            (*customerList_ptr)[customerId] -> setState(CustomerStates::E);

            printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes::GR:
        {
            int orderID = task -> getTaskPayload() -> getOrderID();

            (*customerList_ptr)[customerId] -> setState(CustomerStates::TB);

            (*orderList_ptr)[orderID] -> createReceipt();

            printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes::TR:
        {
            int orderID = task -> getTaskPayload() -> getOrderID();

            (*customerList_ptr)[customerId] -> setState(CustomerStates::PB);

            printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes::FR:
        {
            break;
        }

    }

}

void Waiter::printLog(TaskTypes taskType, int customerId, int orderID)
{       
    switch(taskType)
    {
        case TaskTypes::GM:
            std::cout << "KELNER: " << ID << " PODAJE KARTE DAN KLIENTOWI: " << customerId << std::endl;
            break;

        case TaskTypes::CO:
            std::cout << "KELNER: " << ID << " ODBIERA ZAMOWIENIE: " << orderID << " OD KLIENTA: " << customerId << std::endl;
            break;

        case TaskTypes::DO:
            std::cout << "KELNER: " << ID << " DOSTARCZA ZAMOWIENIE: " << orderID << " DO KLIENTA: " << customerId << std::endl;
            break;

        case TaskTypes::GR:
            std::cout << "KELNER: " << ID << " PODAJE RACHUNEK DO ZAMOWIENIA: " << orderID << " KLIENTOWI: " << customerId << std::endl;
            break;

        case TaskTypes::TR:
            std::cout << "KELNER: " << ID << " POBIERA OPLATE DO ZAMOWIENIA: " << orderID << " OD KLIENTA: " << customerId << std::endl;
            break;

        case TaskTypes::FR:
            std::cout << "KELNER: " << ID << " OCZEKUJE NA ZADANIE " << std::endl;
            break;
    }
}

Waiter::~Waiter() 
{
    for(auto task_ptr : taskQueue)
    {
        delete task_ptr;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////
void Waiter::setState(CustomerStates customerState) {}

CustomerStates Waiter::getState() { return CustomerStates::NEW; }

void Waiter::doAction(std::vector<Person*>* newPersonList, std::vector<Table*>* newTableList, std::vector<Order*>* newOrderList) {}

void Waiter::setOrderID(int newOrderId) {}

void Waiter::setMenu(Menu* new_menu) {}
/////////////////////////////////////////////////////////////////////////////////////////////////