#ifndef TASK_PAYLOAD_H
#define TASK_PAYLOAD_H

#include "Product.h"
#include "Order.h"

#include <vector>

class TaskPayload 
{
    private:
        std::vector<Product*> orderedProductsList;
        Order* order;

    public:
        TaskPayload();

        std::vector<Product*> getOrderedProductsList();
        Order* getOrder();

        void setOrderedProductsList(std::vector<Product*> new_orderedProductsList);
        void setOrder(Order* new_order);

        ~TaskPayload();
};

#endif