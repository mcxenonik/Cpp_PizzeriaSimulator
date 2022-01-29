#ifndef MENU_H
#define MENU_H

#include "Product.h"
#include <vector>

class Menu
{
    private: 
        std::vector<Product*> productList;
        // void createMenu(std::string products_data_file_name);

    public:
        Menu(std::vector<Product*> menuProductsList);

        std::vector<Product*> getProductList();

        ~Menu();
};
    
#endif