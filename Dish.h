#ifndef DISH_H
#define DISH_H

#include "Product.h"

class Dish : public Product
{
    private:
        int eatingTime;

    public:
        Dish(int new_id, std::string new_name, double new_price, int new_eatingTime, int new_prepareTime);

        int getEatingTime();
};

#endif