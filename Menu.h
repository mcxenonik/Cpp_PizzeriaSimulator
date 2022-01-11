#ifndef MENU_H
#define MENU_H

#include "Menu.h"
#include "Product.h"
#include <list>

class Menu
{
    private: 
        std::list<Product*> productList;
        void createMenu();
    public:
        ~Menu();
};
    
#endif