#include "Waiter.h"
#include "Task.h"
#include "TaskTypes.h"

Waiter::Waiter(int new_id, std::string new_name):
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

void Waiter::doTask(Pizzeria *sim_pizzeria)
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
            sim_pizzeria -> getCustomerByID(customerId)->setState(CustomerStates::SO);

            printLog(taskType, customerId, 0);
            break;
        }
        case TaskTypes::CO:
        {
            std::vector<Product*> orderedProductsList = task -> getTaskPayload() -> getOrderedProductsList();

            sim_pizzeria -> getCustomerByID(customerId) -> setState(CustomerStates::WFPO);
            int orderID = sim_pizzeria -> addOrder(customerId, ID, orderedProductsList);
            sim_pizzeria -> getCustomerByID(customerId) -> setOrderID(orderID);

            valueOfCollectedOrdersStat += orderedProductsList[0] -> getPrice() + orderedProductsList[1] -> getPrice();

            printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes::DO:
        {
            int orderID = task -> getTaskPayload() -> getOrderID();
            
            sim_pizzeria->getCustomerByID(customerId)->setState(CustomerStates::E);

            printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes::GR:
        {
            int orderID = task -> getTaskPayload() -> getOrderID();

            sim_pizzeria -> getCustomerByID(customerId) -> setState(CustomerStates::TB);
            sim_pizzeria -> getOrderByID(orderID) -> createReceipt();

            printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes::TR:
        {
            int orderID = task -> getTaskPayload() -> getOrderID();

            sim_pizzeria -> getCustomerByID(customerId) -> setState(CustomerStates::PB);

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
            std::cout << "KELNER:" << ID << "PODAJE KARTE DAN KLIENTOWI:" << customerId;
            break;

        case TaskTypes::CO:
            std::cout << "KELNER:" << ID << "ODBIERA ZAMOWIENIE:" << orderID << "OD KLIENTA:" << customerId;
            break;

        case TaskTypes::DO:
            std::cout << "KELNER:" << ID << "DOSTARCZA ZAMOWIENIE:" << orderID << "DO KLIENTA:" << customerId;
            break;

        case TaskTypes::GR:
            std::cout << "KELNER:" << ID << "PODAJE RACHUNEK DO ZAMOWIENIA:" << orderID << "KLIENTOWI:" << customerId;
            break;

        case TaskTypes::TR:
            std::cout << "KELNER:" << ID << "POBIERA OPLATE DO ZAMOWIENIA:" << orderID << "OD KLIENTA:" << customerId;
            break;

        case TaskTypes::FR:
            std::cout << "KELNER:" << ID << "OCZEKUJE NA ZADANIE";
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