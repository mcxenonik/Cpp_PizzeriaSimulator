#ifndef DRINK_H
#define DRINK_H

#include "Product.h"


class Drink : public Product
{
    private:
        int drinkingTime;

    public:
        Drink(int new_id, std::string new_name, double new_price, int new_drinkingTime);
        int getEatingTime();

};

#endif