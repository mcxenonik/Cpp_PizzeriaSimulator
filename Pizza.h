#ifndef PIZZA_H
#define PIZZA_H

#include "Product.h"

class Pizza : public Product
{
    private:
        int eatingTime;

    public:
        Pizza(int new_id, std::string new_name, int new_price, int new_eatingTime, int new_prepareTime);

        int getEatingTime();

        ~Pizza();

        friend std::ostream& operator<<(std::ostream& os, const Pizza& pizza);
};

std::ostream& operator<<(std::ostream& os, const Pizza& pizza);

#endif