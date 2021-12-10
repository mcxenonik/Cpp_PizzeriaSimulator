from Waiter import Waiter
from Customer import Customer
from Table import Table
from Order import Order
from Menu import Menu
from Task import Task
from TaskTypes import TaskTypes

from random import randint


class Pizzeria:
    def __init__(self, numOfTables=3, numOfWaiters=2, numOfCustomers=6):
        self._waitersList = []
        self._customersList = []
        self._tablesList = []
        self._ordersList = []
        self._menu = None

        self._creatPizzeria(numOfTables, numOfWaiters, numOfCustomers)


    def getWaitersList(self):
        return self._waitersList


    def getCustomersList(self):
        return self._customersList


    def getTableList(self):
        return self._tablesList


    def getOrdersList(self):
        return self._ordersList


    def getMenu(self):
        return self._menu


    def getWaiterByID(self, waiterID):
        return self._waitersList[waiterID]


    def getCustomerByID(self, customerID):
        return self._customersList[customerID]


    def getTableByID(self, tableID):
        return self._tablesList[tableID]


    def getOrderByID(self, orderID):
        return self._ordersList[orderID]


    def getProductByID(self, productID):
        return self._menu[productID]


    def _creatPizzeria(self, numOfTables, numOfWaiters, numOfCustomers):
        self._menu = Menu()

        for i in range(numOfTables):
            self.addTable()

        for i in range(numOfWaiters):
            self.addWaiter()
        
        for i in range(numOfCustomers):
            self.addCustomer()


    def addWaiter(self):
        new_waiter = Waiter(len(self._waitersList))

        self._waitersList.append(new_waiter)

    
    def addCustomer(self):
        new_customer = Customer(len(self._customersList), randint(0, 4))

        self._customersList.append(new_customer)


    def addTable(self):
        new_table = Table(len(self._tablesList), randint(1, 5))

        self._tablesList.append(new_table)


    def addOrder(self, customerID, waiterID, productList):
        new_order = Order(len(self._ordersList), customerID, waiterID, productList)

        self._ordersList.append(new_order)

        return new_order.getID()


    def decreaseOrdersTime(self):
        print("****************************************************************************************")
        for order in self._ordersList:
            if (order.isReady() and not order.isDelivered()):
                new_task = Task(order.getCustomerID(), TaskTypes.DO, order.getID())
                self.getWaiterByID(self.findMinTaskWaiter()).addTask(new_task)
                self.getOrderByID(order.getID()).setIsDelivered(True) 
            elif (not order.isReady()):
                order.decreaseWaitTime()

            print("ORDER ID:", order.getID(), "CUS ID:", order.getCustomerID(), "WAITTIME:", order.getWaitTime(), "IS READY:", order.isReady(), "IS DELIVERED:", order.isDelivered())
        print("****************************************************************************************")


    def findMinTaskWaiter(self):
        min_tasks = self._waitersList[0].getNumberOfTasks()
        waiterID = self._waitersList[0].getID()

        for waiter in self._waitersList:
            if (waiter.getNumberOfTasks() < min_tasks):
                min_tasks = waiter.getNumberOfTasks()
                waiterID = waiter.getID()

        return waiterID


    def countMoney(self):
        money = 0
        for order in self._ordersList:
            money += order.getReceipt().getTotalPrice()

        return money


    def countMinMaxCustomerWaitingTime(self):
        minTime = self._customersList[0].getWaitingTimeState()
        minTimeID = self._customersList[0].getID()
        maxTime = self._customersList[0].getWaitingTimeState()
        maxTimeID = self._customersList[0].getID()

        for customer in self._customersList:
            if (customer.getWaitingTimeState() < minTime):
                minTime = customer.getWaitingTimeState()
                minTimeID = customer.getID()

            if (customer.getWaitingTimeState() > maxTime):
                maxTime = customer.getWaitingTimeState()
                maxTimeID = customer.getID()

        print("MINIMALNY CZAS OCZEKIWANIA:", minTime, "KLIENTA:", minTimeID)
        print("MAKSYMALNY CZAS OCZEKIWANIA:", maxTime, "KLIENTA:", maxTimeID)
        # return minTime, minTimeID, maxTime, maxTimeID


    def countMinMaxWaiterTasksDone(self):
        minTasks = self._waitersList[0].getTasksDoneStat()
        minTasksID = self._waitersList[0].getID()
        maxTasks = self._waitersList[0].getTasksDoneStat()
        maxTasksID = self._waitersList[0].getID()

        for waiter in self._waitersList:
            if (waiter.getTasksDoneStat() < minTasks):
                minTasks = waiter.getTasksDoneStat()
                minTasksID = waiter.getID()

            if (waiter.getTasksDoneStat() > maxTasks):
                maxTasks = waiter.getTasksDoneStat()
                maxTasksID = waiter.getID()

        print("---")
        print("MINIMALNA LICZBA WYKONANYCH ZADAN:", minTasks, "KELNERA:", minTasksID)
        print("MAKSYMALNA LICZBA WYKONANYCH ZADAN:", maxTasks, "KELNERA:", maxTasksID)
        print("---")
        # return minTasks, minTasksID, maxTasks, maxTasksID


    def countMinMaxWaiterValueOfCollectedOrdersStat(self):
        minValue = self._waitersList[0].getValueOfCollectedOrdersStat()
        minValueID = self._waitersList[0].getID()
        maxValue = self._waitersList[0].getValueOfCollectedOrdersStat()
        maxValueID = self._waitersList[0].getID()

        for waiter in self._waitersList:
            if (waiter.getValueOfCollectedOrdersStat() < minValue):
                minValue = waiter.getValueOfCollectedOrdersStat()
                minValueID = waiter.getID()

            if (waiter.getValueOfCollectedOrdersStat() > maxValue):
                maxValue = waiter.getValueOfCollectedOrdersStat()
                maxValueID = waiter.getID()

        print("MINIMALNA WARTOSC PRZYJETYCH ZAMOWIEN:", minValue, "KELNERA:", minValueID)
        print("MAKSYMALNA WARTOSC PRZYJETYCH ZAMOWIEN:", maxValue, "KELNERA:", maxValueID)
        # return minValue, minValueID, maxValue, maxValueID
