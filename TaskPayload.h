#ifndef TASK_PAYLOAD_H
#define TASK_PAYLOAD_H

#include "Product.h"

#include <vector>

class TaskPayload 
{
    private:
        std::vector<Product*> orderedProductsList;
        int orderID;

    public:
        TaskPayload();

        std::vector<Product*> getOrderedProductsList();
        int getOrderID();

        void setOrderedProductsList(std::vector<Product*> new_orderedProductsList);
        void setOrderID(int new_orderID);

        ~TaskPayload();
};

#endif