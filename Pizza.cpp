#include "Pizza.h"

Pizza::Pizza(int new_id, std::string new_name, int new_price, int new_eatingTime, int new_prepareTime) : 
Product(new_id, new_name, new_price, new_prepareTime)
{
    eatingTime = new_eatingTime;
}

int Pizza::getEatingTime()
{
    return eatingTime;
}


