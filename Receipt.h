#ifndef RECEIPT_H
#define RECEIPT_H

#include <vector>
#include "Product.h"

class Receipt
{
    private:
        int ID;
        int orderID;
        bool isPaid;
        std::vector<Product*> productList;
        int totalPrice;

        void countPrice();
    public:
        Receipt(int new_orderID, std::vector<Product*> new_productList);
        int getID();
        int getOrderID();
        bool getIsPaid();
        void paidReceipt();
        int getTotalPrice();
        ~Receipt();
};

#endif