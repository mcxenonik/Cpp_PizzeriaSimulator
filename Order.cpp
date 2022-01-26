#include "Order.h"


Order::Order(int new_id, int new_customerID, int new_waiterID, std::list<Product*> new_productList)
{
    ID = new_id;
    customerID = new_customerID;
    waiterID = new_waiterID;
    isReady = false;
    isDelivered = false;
    isPaid = false;
    waitTime = 0;
    productList  = new_productList;

    setWaitTime();
}

int Order::getID()
{
    return ID;
}

int Order::getCustomerID()
{
    return customerID;
}

int Order:: getWaiterID()
{
    return waiterID;
}

bool Order::getIsReady()
{
    return isReady;
}

bool Order::getIsDelivered()
{
    return isDelivered;
}

bool Order::getIsPaid()
{
    return isPaid;
}

std::vector<Product*> Order::getProductList()
{
    return productList;
}

int Order::getWaitTime()
{
    return waitTime;
}

Receipt* Order::getReceipt()
{
    return receipt;
}

void Order::setPaid()
{
    isPaid = true;
}

void Order::createReceipt()
{
    receipt = new Receipt(ID, productList);
    std::cout << "RACHUNEK: " << receipt->getTotalPrice() << " DO ZAMOWIENIA: " << ID << std::endl;
}

void Order::setIsDelivered(bool new_isDelivered)
{
    isDelivered = new_isDelivered;
}

void Order::setWaiterID(int new_waiterID)
{
    waiterID = new_waiterID;
}

void Order::setWaitTime()
{
    for (auto product_ptr : productList)
    {
        waitTime += product_ptr->getPrepareTime();
    }
    if (waitTime == 0)
    {
        isReady = true;
    }
}

void Order::decreaseWaitTime()
{
    waitTime -= 1;
    if (waitTime == 0)
    {
        isReady = true;
    }
}
Order::~Order()
{
    for (auto product_ptr : productList)
    {
        delete product_ptr;
    }
    delete receipt;
}