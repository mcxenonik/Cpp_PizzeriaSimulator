from Receipt import Receipt

class Order:
    def __init__(self, new_id, new_customerID, new_waiterID, new_productList):
        self._ID = new_id
        self._customerID = new_customerID
        self._waiterID = new_waiterID
        self._isReady = False
        self._isDelivered = False
        self._isPaid = False
        self._waitTime = 0
        self._productList  = new_productList
        self._receipt = None

        self._setWaitTime()


    def getID(self):
        return self._ID


    def getCustomerID(self):
        return self._customerID


    def getWaiterID(self):
        return self._waiterID


    def isReady(self):
        return self._isReady


    def isDelivered(self):
        return self._isDelivered


    def isPaid(self):
        return self._isPaid


    def getProductList(self):
        return self._productList


    def getWaitTime(self):
        return self._waitTime


    def getReceipt(self):
        return self._receipt


    def setPaid(self):
        self._isPaid = True


    def createReceipt(self):
        self._receipt = Receipt(self._ID, self._productList)
        # print("RACHUNEK:", self._receipt.getTotalPrice(), "DO ZAMOWIENIA:", self._ID)


    def setIsDelivered(self, isDelivered):
        self._isDelivered = isDelivered


    def setWaiterID(self, new_waiterID):
        self._waiterID = new_waiterID


    def _setWaitTime(self):
        for product in self._productList:   
            self._waitTime += product.getPrepareTime()

        if (self._waitTime == 0):
            self._isReady = True


    def decreaseWaitTime(self):
        self._waitTime -= 1

        if (self._waitTime == 0):
            self._isReady = True
