#ifndef WAITER_H
#define WAITER_H

#include "Person.h"
#include "CustomerStates.h"
#include "TaskTypes.h"
#include "Task.h"
#include "Pizzeria.h"

#include <vector>

class Waiter : public Person
{
    private:
        std::vector<Task*> taskQueue;
        int tasksDoneStat;
        int valueOfCollectedOrdersStat;
        
        
    public:
        Waiter(int new_id, std::string new_name);

        int getTasksDoneStat();
        int getValueOfCollectedOrdersStat();

        int getNumberOfTasks();
        void addTask(Task *new_task);
        void doTask(std::vector<Customer*>* customerList_ptr, std::vector<Order*>* orderList_ptr);
        void printLog(TaskTypes taskType, int customerID, int orderID);

        ~Waiter();
};

#endif