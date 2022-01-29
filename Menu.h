#ifndef MENU_H
#define MENU_H

#include "Product.h"
#include <vector>

class Menu
{
    private: 
        std::vector<Product*> productList;
        void createMenu();

    public:
        Menu();

        std::vector<Product*> getProductList();

        ~Menu();
};
    
#endif