#ifndef ORDER_H
#define ORDER_H

#include "Receipt.h"
#include "Product.h"
#include <iostream>
#include <vector>

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
        std::vector<Product*> productList;
        Receipt *receipt;
        void setWaitTime();
        
    public:
        Order(int new_id, int new_customerID, int new_waiterID, std::vector<Product*> new_productList);
        int  getID();
        int getCustomerID();
        int getWaiterID();
        bool getIsReady();
        bool getIsDelivered();
        bool getIsPaid();
        std::vector<Product*> getProductList();
        int getWaitTime();
        Receipt* getReceipt();
        void setPaid();
        void createReceipt();
        void setIsDelivered(bool isDelivered);
        void setWaiterID(int new_waiterID);
        void decreaseWaitTime();
        ~Order();
};

#endif