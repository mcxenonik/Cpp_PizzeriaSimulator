#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "CustomerStates.h"
#include "TaskTypes.h"
#include "Task.h"
#include "TaskPayload.h"
#include "Pizzeria.h"
#include "Product.h"

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
        void orderMenu(std::vector<Waiter*>* waiterList_ptr);
        void waitForMenu();
        void submitOrder(std::vector<Waiter*>* waiterList_ptr);
        void waitForAcceptOrder();
        void waitForPrepareOrder();
        void eat();
        void askForBill(std::vector<Waiter*>* waiterList_ptr);
        void waitForBill();
        void takeBill(std::vector<Waiter*>* waiterList_ptr);
        void waitForPayBill();
        void payBill(std::vector<Order*>* orderList_ptr);
        void out(std::vector<Table*>* tableList_ptr);

        Waiter* findMinTaskWaiter(std::vector<Waiter*>* waiterList_ptr);
        
        
    public:
        Customer(int new_id, std::string new_name, int new_groupID);

        CustomerStates getState();
        int getGroupID();
        int getTableID();
        int getOrderID();
        int getEatTime();
        int getWaitingTimeState();

        void setTableID(int new_tableID);
        void setOrderID(int new_orderID);
        void setEatTime(int new_eatTime);
        void setState(CustomerStates new_state);

        void doAction(std::vector<Waiter*>* waiterList_ptr, std::vector<Table*>* tableList_ptr, std::vector<Order*>* orderList_ptr);

        void printLog(bool result, int totalPrice);

        ~Customer();
};

#endif