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

        bool takeTable(Pizzeria *simulated_pizzeria);
        void waitForFreeTable();
        void orderMenu(Pizzeria *simulated_pizzeria);
        void waitForMenu();
        void submitOrder(Pizzeria *simulated_pizzeria);
        void waitForAcceptOrder();
        void waitForPrepareOrder();
        void eat();
        void askForBill(Pizzeria *simulated_pizzeria);
        void waitForBill();
        void takeBill(Pizzeria *simulated_pizzeria);
        void waitForPayBill();
        void payBill(Pizzeria *simulated_pizzeria);
        void out(Pizzeria *simulated_pizzeria);
        
        void doAction(Pizzeria *simulated_pizzeria);

        void printLog(bool result, int totalPrice);

        ~Customer();
};

#endif