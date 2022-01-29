#include "Dish.h"

#include <iostream>

Dish::Dish(int new_id, std::string new_name, double new_price, int new_eatingTime, int new_prepareTime) : 
Product(new_id, new_name, new_price, new_prepareTime)
{
    eatingTime = new_eatingTime;
}

int Dish::getEatingTime()
{
    return eatingTime;
}

std::ostream& operator<<(std::ostream& os, const Dish& dish)
{
    os << dish.ID << " | " << dish.name << " | " << dish.price << std::endl;
    return os;
}

Dish::~Dish()
{
    
}