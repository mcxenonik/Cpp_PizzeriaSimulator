#ifndef WAITER_H
#define WAITER_H

#include "Person.h"
#include "CustomerStates.h"
#include "TaskTypes.h"
#include "Task.h"
#include "Table.h"
#include "Order.h"

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

        int getNumberOfTasks() override;
        void addTask(Task *new_task) override;
        void doTask(std::vector<Person*>* customerList_ptr, std::vector<Order*>* orderList_ptr) override;
        void printLog(TaskTypes taskType, int customerID, int orderID);

        ~Waiter();

        void setState(CustomerStates customerState) override;
        CustomerStates getState() override;
        void doAction(std::vector<Person*>* newPersonList, std::vector<Table*>* newTableList, std::vector<Order*>* newOrderList) override;
        void setOrderID(int newOrderId) override;
};

#endif