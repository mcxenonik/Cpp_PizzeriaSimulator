#ifndef RECEIPT_H
#define RECEIPT_H

#include <list>
#include "Product.h"

class Receipt
{
    private:
        int ID;
        int orderID;
        bool isPaid;
        std::list<Product*> productList;
        int totalPrice;

        void countPrice();
    public:
        Receipt(int new_orderID, std::list<Product*> new_productList);
        int getID();
        int getOrderID();
        bool getIsPaid();
        void paidReceipt();
        int getTotalPrice();
        ~Receipt();
};

#endif