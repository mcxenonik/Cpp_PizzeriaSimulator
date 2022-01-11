#ifndef PRODUCT_H
#define PRODUCT_H

#include "productInterface.h"


class Product : public ProductInterface
{
    protected: 
        int ID;
        std::string name;
        int price;
        int prepareTime;

    public:
        Product(int new_id, std::string new_name, int new_price, int new_prepareTime);
        int getID();
        std::string getName();
        int getPrice();
        int getPrepareTime();
        virtual ~Product() {}
};
    
#endif