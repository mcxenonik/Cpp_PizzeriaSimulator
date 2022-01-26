#include "TaskPayload.h"

TaskPayload::TaskPayload()
{

}

std::vector<Product*> TaskPayload::getOrderedProductsList()
{
    return orderedProductsList;
}

int TaskPayload::getOrderID()
{
    return orderID;
}

void TaskPayload::setOrderedProductsList(std::vector<Product*> new_orderedProductsList)
{
    orderedProductsList = new_orderedProductsList;
}

void TaskPayload::setOrderID(int new_orderID)
{
    orderID = new_orderID;
}

TaskPayload::~TaskPayload()
{
    for(auto orderedProduct_ptr : orderedProductsList)
    {
        delete orderedProduct_ptr;
    }
}