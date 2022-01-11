
#include "Receipt.h"

Receipt::Receipt(int new_orderID, std::list<Product*> new_productList)
{
    ID = new_orderID;
    orderID = new_orderID;
    isPaid = false;    
    totalPrice = 0;
    for (auto product_ptr : new_productList)
    {
        productList.push_back(product_ptr);
    }
}

void Receipt::countPrice()
{
    for (auto product_ptr : productList)
    {
        totalPrice += product_ptr->getPrice();
    }
}

int Receipt::getID()
{
    return ID;
}

int Receipt::getOrderID()
{
    return orderID;
}

bool Receipt::getIsPaid()
{
    return isPaid;
}

void Receipt::paidReceipt()
{
    isPaid = true;
}

int Receipt::getTotalPrice()
{
    return totalPrice;
}

Receipt::~Receipt()
{
    for (auto product_ptr : productList)
    {
        delete product_ptr;
    }
}