#ifndef ORDER_H
#define ORDER_H

#include "Receipt.h"
#include <iostream>

class Order
{
    private:
        int ID;
        int customerID;
        int waiterID;
        bool isReady;
        bool isDelivered;
        bool isPaid;
        int waitTime;
        std::list<Product*> productList;
        Receipt *receipt = nullptr;
        void setWaitTime();
    public:
        Order(int new_id, int new_customerID, int new_waiterID, std::list<Product*> new_productList);
        int  getID();
        int getCustomerID();
        int getWaiterID();
        bool getIsReady();
        bool getIsDelivered();
        bool getIsPaid();
        std::list<Product*> getProductList();
        int getWaitTime();
        Receipt getReceipt();
        void setPaid();
        void createReceipt();
        void setIsDelivered(bool isDelivered);
        void setWaiterID(int new_waiterID);
        void decreaseWaitTime();
        ~Order();
};

#endif