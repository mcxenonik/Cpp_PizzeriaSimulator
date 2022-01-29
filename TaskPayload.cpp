#include "TaskPayload.h"

TaskPayload::TaskPayload()
{

}

std::vector<Product*> TaskPayload::getOrderedProductsList()
{
    return orderedProductsList;
}

Order* TaskPayload::getOrder()
{
    return order;
}

void TaskPayload::setOrderedProductsList(std::vector<Product*> new_orderedProductsList)
{
    for (auto product_ptr : new_orderedProductsList)
    {
        orderedProductsList.push_back(product_ptr);
    }
}

void TaskPayload::setOrder(Order* new_order)
{
    order = new_order;
}

TaskPayload::~TaskPayload()
{

}