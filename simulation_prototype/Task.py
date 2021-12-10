from random import randint


class Task:
    def __init__(self, new_customerID, new_taskType, new_payload=None):
        self._ID = randint(0, 100000)
        self._customerID = new_customerID
        self._taskType = new_taskType
        self._payload = new_payload


    def getID(self):
        return self._ID


    def getCustomerID(self):
        return self._customerID


    def getTaskType(self):
        return self._taskType

    
    def getPayload(self):
        return self._payload