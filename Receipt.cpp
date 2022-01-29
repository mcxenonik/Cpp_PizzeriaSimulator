
#include "Receipt.h"

Receipt::Receipt(int new_orderID, std::vector<Product*> new_productList)
{
    ID = new_orderID;
    orderID = new_orderID;
    isPaid = false;    
    totalPrice = 0;
    
    setProducts(new_productList);
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

void Receipt::setProducts(std::vector<Product*> new_productList)
{
    for (auto product_ptr : new_productList)
    {
        productList.push_back(product_ptr);

        totalPrice += product_ptr -> getPrice();
    }
}

Receipt::~Receipt()
{

}