#include "Menu.h"

Menu::Menu(std::vector<Product*> menuProductsList)
{
    for (auto product_ptr : menuProductsList)
    {
        productList.push_back(product_ptr);
    }
}

std::vector<Product*> Menu::getProductList()
{
    return productList;
}

Menu::~Menu()
{
    for(auto product : productList)
    {
        delete product;
    }
}