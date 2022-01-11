#include "Drink.h"


Drink::Drink(int new_id, std::string new_name, double new_price, 
            int new_drinkingTime): Product(new_id, new_name, new_price, 0)
{
    drinkingTime = new_drinkingTime;
}

int Drink::getEatingTime()
{
    return drinkingTime;
}