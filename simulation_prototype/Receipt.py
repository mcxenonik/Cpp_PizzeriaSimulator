class Receipt:
    def __init__(self, new_orderID, new_productList):
        self._ID = new_orderID
        self._orderID = new_orderID
        self._isPaid = False
        self._productList = new_productList
        self._totalPrice = 0

        self._countPrice()


    def getID(self):
        return self._ID


    def getOrderID(self):
        return self._orderID


    def isPaid(self):
        return self._isPaid


    def paidReceipt(self):
        self._isPaid = True


    def getTotalPrice(self):
        return self._totalPrice


    def _countPrice(self):
        for product in self._productList:
            self._totalPrice += product.getPrice()