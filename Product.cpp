#include "Product.h"

#include <iostream>

Product::Product(int new_id, std::string new_name, int new_price, int new_prepareTime)
{
    ID = new_id;
    name = new_name;
    price = new_price;
    prepareTime = new_prepareTime;
}

int Product::getID()
{
    return ID;
}
std::string Product::getName()
{
    return name;
}
int Product::getPrice()
{
    return price;
}
int Product::getPrepareTime()
{
    return prepareTime;
}

std::ostream& operator<<(std::ostream& os, const Product& product)
{
    os << product.ID << " | " << product.name << " | " << product.price << std::endl;
    return os;
}