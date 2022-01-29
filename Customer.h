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
        Table* table;
        Order* order;
        Menu* menu;
        int eatTime;
        int waitingTimeStat;
        
        Person* findMinTaskWaiter(std::vector<Person*>* waiterList_ptr);

        bool takeTable(std::vector<Table*>* tableList_ptr);
        void orderMenu(std::vector<Person*>* waiterList_ptr);
        void submitOrder(std::vector<Person*>* waiterList_ptr);
        void askForReceipt(std::vector<Person*>* waiterList_ptr);
        void takeReceipt(std::vector<Person*>* waiterList_ptr);
        void waitForPrepareOrder();
        void waitForAcceptOrder();
        void waitForPayReceipt();
        void waitForFreeTable();
        void waitForReceipt();
        void waitForMenu();
        void payReceipt();
        void eat();
        void out();
  
    public:
        Customer(int new_id, std::string new_name, int new_groupID);

        int getWaitingTimeState();
        CustomerStates getState() override;
        void setOrder(Order* new_order) override;
        void setState(CustomerStates new_state) override;
        void setMenu(Menu* new_menu) override;
        void doAction(std::vector<Person*>* waiterList_ptr, std::vector<Table*>* tableList_ptr) override;

        void printLog(bool result, int totalPrice);

        ~Customer();

        int getNumberOfTasks() override;
        void addTask(Task*) override;
        void doTask(std::vector<Person*>*, std::vector<Order*>*) override;
};

#endif