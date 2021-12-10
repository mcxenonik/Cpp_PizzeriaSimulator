from Product import Product


class Pizza(Product):
    def __init__(self, new_id, new_name, new_price, new_eatingTime, new_prepareTime):
        super().__init__(new_id, new_name, new_price, new_prepareTime)

        self._eatingTime = new_eatingTime


    def __str__(self):
        return "NAME:" + self._name


    def getEatingTime(self):
        return self._eatingTime
