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

void Waiter::doTask(Pizzeria &sim_pizzeria)
{
    if(this.taskQueue.length() == 0)
    {
        this.printLog();
        return;
    }

    this.tasksDoneStat += 1;

    Task* task = this.taskQueue.pop();
    TaskTypes taskType = task.getTaskType();
    int customerId = task.getCustomerID();

    switch(taskType)
    {
        case TaskTypes.GM:
        {
            sim_pizzeria.getCustomerByID(customerId).setState(CustomerStates.SO);

            this.printLog(taskType, customerId);
            break;
        }
        case TaskTypes.CO:
        {
            std::vector<Product*> orderedProductsList = task.getPayload();

            sim_pizzeria.getCustomerByID(customerId).setState(CustomerStates.WFPO);
            int orderID = sim_pizzeria.addOrder(customerId, this.ID, orderedProductsList);
            sim_pizzeria.getCustomerByID(customerId).setOrderID(orderID);

            this.valueOfCollectedOrdersStat += orderedProductsList[0].getPrice() + orderedProductsList[1].getPrice();

            this.printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes.DO:
        {
            int orderID = task.getPayload();
            
            sim_pizzeria.getCustomerByID(customerId).setState(CustomerStates.E);

            this.printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes.GR:
        {
            int orderID = task.getPayload();

            sim_pizzeria.getCustomerByID(customerId).setState(CustomerStates.TB);
            sim_pizzeria.getOrderByID(orderID).createReceipt();

            this.printLog(taskType, customerId, orderID);
            break;
        }
        case TaskTypes.TR:
        {
            int orderID = task.getPayload();

            sim_pizzeria.getCustomerByID(customerId).setState(CustomerStates.PB);

            this.printLog(taskType, customerId, orderID);
            break;
        }
        default:
        {
            break;
        }

    }

}

void Waiter::printLog(TaskTypes taskType, int customerID, int orderID)
{       
    switch(taskType)
    {
        case TaskTypes.GM:
            print("KELNER:", this.ID, "PODAJE KARTE DAN KLIENTOWI:", customerId);
            break;

        case TaskTypes.CO:
            print("KELNER:", this.ID, "ODBIERA ZAMOWIENIE:", orderID, "OD KLIENTA:", customerId);
            break;

        case TaskTypes.DO:
            print("KELNER:", this.ID, "DOSTARCZA ZAMOWIENIE:", orderID, "DO KLIENTA:", customerId);
            break;

        case TaskTypes.GR:
            print("KELNER:", this.ID, "PODAJE RACHUNEK DO ZAMOWIENIA:", orderID, "KLIENTOWI:", customerId);
            break;

        case TaskTypes.TR:
            print("KELNER:", this.ID, "POBIERA OPLATE DO ZAMOWIENIA:", orderID, "OD KLIENTA:", customerId);
            break;

        default:
            print("KELNER:", this.ID, "OCZEKUJE NA ZADANIE");
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