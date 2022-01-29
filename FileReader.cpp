#include "FileReader.h"

#include "Product.h"
#include "Pizza.h"
#include "Drink.h"
#include "Dish.h"

#include "json/json.hpp"
#include <fstream>

FileReader::FileReader()
{

}

std::vector<int> FileReader::readSimulationParameters(std::string simulation_parameters_file_name)
{
    std::ifstream filestream(simulation_parameters_file_name);

    std::vector<int> parametersList;
    std::string parameter_name;
    int parameter_value;

    while (filestream >> parameter_name >> parameter_value)
    {
        parametersList.push_back(parameter_value);
    };

    return parametersList;
}

std::vector<Product*> FileReader::readProductsData(std::string products_data_file_name)
{
    using json = nlohmann::json;
    std::ifstream filestream(products_data_file_name);
    json jsonFile;
    filestream >> jsonFile;
    
    std::vector<Product*> productList;
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

    return productList;
}

FileReader::~FileReader()
{
    
}