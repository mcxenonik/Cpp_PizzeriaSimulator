#include "Menu.h"
#include "Product.h"
#include "Pizza.h"
#include "Drink.h"
#include "Dish.h"

#include "json/json.hpp"

#include <iostream>
#include <fstream>
#include <string>

Menu::Menu()
{
    createMenu();
}

void Menu::createMenu()
{
    using json = nlohmann::json;
    std::ifstream filestream("products_data.json");
    json jsonFile;
    filestream >> jsonFile;
    
    Product *newProduct;
    for (json::iterator it = jsonFile.begin(); it != jsonFile.end(); ++it) 
    {
        if((*it)["type"] == "Pizza")
        {
            newProduct = new Pizza(productList.size(), (*it)["name"], std::stoi(std::string((*it)["price"])), std::stoi(std::string((*it)["eatingTime"])), std::stoi(std::string((*it)["prepareTime"])));
        }
        else if((*it)["type"] == "Drink")
        {
            newProduct = new Drink(productList.size(), (*it)["name"], std::stoi(std::string((*it)["price"])), std::stoi(std::string((*it)["drinkingTime"])));
        }
        else if((*it)["type"] == "Dish")
        {
            newProduct = new Dish(productList.size(), (*it)["name"], std::stoi(std::string((*it)["price"])), std::stoi(std::string((*it)["eatingTime"])), std::stoi(std::string((*it)["prepareTime"])));
        }
        
        productList.push_back(newProduct);
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