from Product import Product


class Drink(Product):
    def __init__(self, new_id, new_name, new_price, new_drinkingTime):
        super().__init__(new_id, new_name, new_price, 0)

        self._drinkingTime = new_drinkingTime


    def __str__(self):
        return "NAME:" + self._name


    def getEatingTime(self):
        return self._drinkingTime