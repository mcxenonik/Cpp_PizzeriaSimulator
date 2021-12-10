import json

from Pizza import Pizza
from Drink import Drink

class Menu:
    def __init__(self):
        self._productList  = []
  
        self._creatMenu()


    def getProductList(self):
        return self._productList


    def getProductByID(self, productID):
        return self._productList[productID]


    def _creatMenu(self):
        with open("products_data.json") as file:
            textMenu = json.load(file)

        for product in textMenu:
            if (textMenu[product]["type"] == "Pizza"):
                new_product = Pizza(len(self._productList), textMenu[product]["name"], int(textMenu[product]["price"]), int(textMenu[product]["eatingTime"]), int(textMenu[product]["prepareTime"]))
            elif (textMenu[product]["type"] == "Drink"):
                new_product = Drink(len(self._productList), textMenu[product]["name"], int(textMenu[product]["price"]), int(textMenu[product]["drinkingTime"]))

            self._productList.append(new_product)
