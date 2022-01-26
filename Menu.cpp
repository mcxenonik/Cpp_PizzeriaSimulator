#include "Menu.h"

#include <iostream>
#include "json/json.hpp"
#include <fstream>
#include "Product.h"
#include "Pizza.h"
#include "Drink.h"
#include <list>
#include <string>

Menu::Menu()
{
    createMenu();
}

void Menu::createMenu()
{
    using json = nlohmann::json;
    std::ifstream i("products_data.json");
    json j;
    i >> j;
    
    Product *newProduct;
    for (json::iterator it = j.begin(); it != j.end(); ++it) 
    {
        if((*it)["type"] == "Pizza")
        {
            newProduct = new Pizza(productList.size(), (*it)["name"], std::stoi(std::string((*it)["price"])), std::stoi(std::string((*it)["eatingTime"])), std::stoi(std::string((*it)["prepareTime"])));
        }
        else if((*it)["type"] == "Drink")
        {
            newProduct = new Drink(productList.size(), (*it)["name"], std::stoi(std::string((*it)["price"])), std::stoi(std::string((*it)["drinkingTime"])));
        }
        
        productList.push_back(newProduct);
    }
}

std::vector<Product*> Menu::getProductList()
{
    return productList;
}

Product* Menu::getProductByID(int productID)
{
    return productList[productID];
}

Menu::~Menu()
{
    for(auto product : productList)
    {
        delete product;
    }
}