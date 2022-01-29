#include "Drink.h"

#include <iostream>

Drink::Drink(int new_id, std::string new_name, double new_price, 
            int new_drinkingTime): Product(new_id, new_name, new_price, 0)
{
    drinkingTime = new_drinkingTime;
}

int Drink::getEatingTime()
{
    return drinkingTime;
}

std::ostream& operator<<(std::ostream& os, const Drink& drink)
{
    os << drink.ID << " | " << drink.name << " | " << drink.price << std::endl;
    return os;
}

Drink::~Drink()
{
    
}