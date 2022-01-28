#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "CustomerStates.h"
#include "TaskTypes.h"
#include "Task.h"
#include "TaskPayload.h"
#include "Product.h"
#include "Table.h"
#include "Order.h"

#include <vector>
#include <random>

#include <algorithm>
#include <iostream>
#include <iterator>

class Customer : public Person
{
    private:
        CustomerStates state;
        int groupID;
        int tableID;
        int orderID;
        int eatTime;
        int waitingTimeStat;

        bool takeTable(std::vector<Table*>* tableList_ptr);
        void waitForFreeTable();
        void orderMenu(std::vector<Person*>* waiterList_ptr);
        void waitForMenu();
        void submitOrder(std::vector<Person*>* waiterList_ptr);
        void waitForAcceptOrder();
        void waitForPrepareOrder();
        void eat();
        void askForBill(std::vector<Person*>* waiterList_ptr);
        void waitForBill();
        void takeBill(std::vector<Person*>* waiterList_ptr);
        void waitForPayBill();
        void payBill(std::vector<Order*>* orderList_ptr);
        void out(std::vector<Table*>* tableList_ptr);

        Person* findMinTaskWaiter(std::vector<Person*>* waiterList_ptr);
        
        
    public:
        Customer(int new_id, std::string new_name, int new_groupID);

        CustomerStates getState() override;
        int getGroupID();
        int getTableID();
        int getOrderID();
        int getEatTime();
        int getWaitingTimeState();

        void setTableID(int new_tableID);
        void setOrderID(int new_orderID) override;
        void setEatTime(int new_eatTime);
        void setState(CustomerStates new_state) override;

        void doAction(std::vector<Person*>* waiterList_ptr, std::vector<Table*>* tableList_ptr, std::vector<Order*>* orderList_ptr) override;

        void printLog(bool result, int totalPrice);

        ~Customer();

        int getNumberOfTasks() override;
        void addTask(Task* new_task) override;
        void doTask(std::vector<Person*>* newPersonList, std::vector<Order*>* newOrderList) override;
};

#endif