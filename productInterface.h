#ifndef PRODUCT_INTERFACE_H
#define PRODUCT_INTERFACE_H

#include <string>

class ProductInterface
{
    public:
        virtual int getID() = 0;
        virtual std::string getName() = 0;
        virtual int getPrice() = 0;
        virtual int getPrepareTime() = 0;
        virtual int getEatingTime() = 0;
};

#endif