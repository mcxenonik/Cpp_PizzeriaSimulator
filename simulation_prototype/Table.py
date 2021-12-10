class Table:
    def __init__(self, new_id, new_size):
        self._ID = new_id
        self._size = new_size
        self._isFull = False
        self._groupID = None
        self._customersIDList = []


    def getID(self):
        return self._ID


    def getSize(self):
        return self._size


    def isFull(self):
        return self._isFull


    def getGroupID(self):
        return self._groupID


    def getCustomersIDList(self):
        return self._customersIDList


    def addCustomerToTable(self, customerID, customerGroupID):
        self._customersIDList.append(customerID)

        if (self._groupID is None):
            self._groupID = customerGroupID

        if (len(self._customersIDList) == self._size):
            self._isFull = True


    def deleteCustomerFromTable(self, customerID):
        self._customersIDList.remove(customerID)
        self._groupID = None
        self._isFull = False
