#include "Waiter.h"

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

void Waiter::doTask(Pizzeria &simulated_pizzeria)
{
    
}

void Waiter::printLog(TaskTypes taskType, int customerID, int orderID)
{
    
}

Waiter::~Waiter() 
{
    for(auto task_ptr : taskQueue)
    {
        delete task_ptr;
    }
}