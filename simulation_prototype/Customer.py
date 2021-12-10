from random import choice
from Person import Person
from Task import Task
from CustomerStates import CustomerStates
from TaskTypes import TaskTypes


class Customer(Person):
    def __init__(self, new_id, new_groupID):
        super().__init__(new_id)

        self._groupID = new_groupID
        self._state = CustomerStates.NEW
        self._tableID = None
        self._orderID = None
        self._eatTime = 0
        self._waitingTimeStat = 0


    def getGroupID(self):
        return self._groupID


    def getState(self):
        return self._state


    def getTableID(self):
        return self._tableID


    def getOrderID(self):
        return self._orderID


    def getEatTime(self):
        return self._eatTime


    def getWaitingTimeState(self):
        return self._waitingTimeStat


    def setTableID(self, new_tableID):
        self._tableID = new_tableID


    def setOrderID(self, new_orderID):
        self._orderID = new_orderID

    def setEatTime(self, new_eatTime):
        self._eatTime = new_eatTime


    def addEatTime(self, eatTime_to_add):
        self._eatTime += eatTime_to_add


    def decreaseEatTime(self):
        self._eatTime -= 1


    def setState(self, new_state):
        self._state = new_state


    def zajmij_stolik(self, sim_pizzeria):
        for table in sim_pizzeria.getTableList():
            if (table.getGroupID() == self._groupID and not table.isFull()):
                table.addCustomerToTable(self._ID, self._groupID)
                self._tableID = table.getID()
                return True

        for table in sim_pizzeria.getTableList():
            if (table.getGroupID() == None):
                table.addCustomerToTable(self._ID, self._groupID)
                self._tableID = table.getID()
                return True

        return False


    def oczekuj_na_wolny_stolik(self):
        self._waitingTimeStat += 1


    def zamow_karte_dan(self, sim_pizzeria):
        waiterID = sim_pizzeria.findMinTaskWaiter()

        new_task = Task(self._ID, TaskTypes.GM)
        sim_pizzeria.getWaiterByID(waiterID).addTask(new_task)


    def oczekuj_na_karte_dan(self):
        self._waitingTimeStat += 1


    def zloz_zamowienie(self, sim_pizzeria):
        waiterID = sim_pizzeria.findMinTaskWaiter()

        productList = sim_pizzeria.getMenu().getProductList()
        orderedProductsList = [choice(productList), choice(productList)]
        self._eatTime = orderedProductsList[0].getEatingTime() + orderedProductsList[1].getEatingTime()
        
        new_task = Task(self._ID, TaskTypes.CO, orderedProductsList)
        sim_pizzeria.getWaiterByID(waiterID).addTask(new_task)


    def oczekuj_na_przyjecie_zamowienia(self):
        self._waitingTimeStat += 1


    def oczekuj_na_przygotowanie_zamowienia(self):
        self._waitingTimeStat += 1


    def zjedz(self):
        self.decreaseEatTime()


    def popros_o_rachunek(self, sim_pizzeria):
        waiterID = sim_pizzeria.findMinTaskWaiter()

        new_task = Task(self._ID, TaskTypes.GR, self._orderID)
        sim_pizzeria.getWaiterByID(waiterID).addTask(new_task)


    def oczekuj_na_rachunek(self):
        self._waitingTimeStat += 1


    def wez_rachunek(self, sim_pizzeria):
        waiterID = sim_pizzeria.findMinTaskWaiter()

        new_task = Task(self._ID, TaskTypes.TR, self._orderID)
        sim_pizzeria.getWaiterByID(waiterID).addTask(new_task)


    def oczekuj_na_pobranie_oplaty(self):
        self._waitingTimeStat += 1


    def oplac_rachunek(self, sim_pizzeria):
        sim_pizzeria.getOrderByID(self._orderID).getReceipt().paidReceipt()
        sim_pizzeria.getOrderByID(self._orderID).setPaid()


    def wyjdz(self, sim_pizzeria):
        if (self._tableID is not None):
            sim_pizzeria.getTableByID(self._tableID).deleteCustomerFromTable(self._ID)
            self._tableID = None
    

    def doAction(self, sim_pizzeria):
        if (self._state == CustomerStates.NEW):
            result = self.zajmij_stolik(sim_pizzeria)

            if (result):
                self.printLog(result)
                self._state = CustomerStates.OM
            else:
                self.oczekuj_na_wolny_stolik()

                self.printLog(result)
                self._state = CustomerStates.NEW

        elif (self._state == CustomerStates.OM):
            self.zamow_karte_dan(sim_pizzeria)

            self.printLog()
            self._state = CustomerStates.WFM

        elif (self._state == CustomerStates.WFM):
            self.oczekuj_na_karte_dan()

            self.printLog()
            self._state = CustomerStates.WFM

        elif (self._state == CustomerStates.SO):
            self.zloz_zamowienie(sim_pizzeria)

            self.printLog()
            self._state = CustomerStates.WFAO

        elif (self._state == CustomerStates.WFAO):
            self.oczekuj_na_przyjecie_zamowienia()

            self.printLog()
            self._state = CustomerStates.WFAO

        elif (self._state == CustomerStates.WFPO):
            self.oczekuj_na_przygotowanie_zamowienia()

            self.printLog()
            self._state = CustomerStates.WFPO

        elif (self._state == CustomerStates.E):
            self.zjedz()

            if (self._eatTime == 0):
                self.printLog()
                self._state = CustomerStates.AFB
            else:
                self.printLog()
                self._state = CustomerStates.E

        elif (self._state == CustomerStates.AFB):
            self.popros_o_rachunek(sim_pizzeria)

            self.printLog()
            self._state = CustomerStates.WFB

        elif (self._state == CustomerStates.WFB):
            self.oczekuj_na_rachunek()

            self.printLog()
            self._state = CustomerStates.WFB

        elif (self._state == CustomerStates.TB):
            self.wez_rachunek(sim_pizzeria)

            self.printLog(False, sim_pizzeria.getOrderByID(self._orderID).getReceipt().getTotalPrice())
            self._state = CustomerStates.WFPB

        elif (self._state == CustomerStates.WFPB):
            self.oczekuj_na_pobranie_oplaty()

            self.printLog()
            self._state = CustomerStates.WFPB

        elif (self._state == CustomerStates.PB):
            self.oplac_rachunek(sim_pizzeria)

            self.printLog(False, sim_pizzeria.getOrderByID(self._orderID).getReceipt().getTotalPrice())
            self._state = CustomerStates.OUT

        elif (self._state == CustomerStates.OUT):
            self.wyjdz(sim_pizzeria)

            self.printLog()
            self._state = CustomerStates.OUT
    

    def printLog(self, result=False, totalPrice=None):
        if (self._state == CustomerStates.NEW):
            if (result):
                print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "ZAJMUJE STOLIK:", self._tableID)
            else:
                print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "OCZEKUJE NA WOLNY STOLIK")

        elif (self._state == CustomerStates.OM):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "ZAMOWIL KARTE DAN")

        elif (self._state == CustomerStates.WFM):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "OCZEKUJE NA KARTE DAN")

        elif (self._state == CustomerStates.SO):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "SKŁADA ZAMOWIENIE")

        elif (self._state == CustomerStates.WFAO):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "OCZEKUJE NA PRZYJECIE ZAMOWIENIA")

        elif (self._state == CustomerStates.WFPO):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "OCZEKUJE NA PRZYGOTOWANIE ZAMOWIENIA")

        elif (self._state == CustomerStates.E):
            if (self._eatTime != 0):
                print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "SPOZYWA ZAMOWIENIE. POZOSTALO:", self._eatTime)
            else:
                print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "SKONCZYL SPOZYWANIE ZAMOWIENIA")

        elif (self._state == CustomerStates.AFB):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "POPROSIL O RACHUNEK")

        elif (self._state == CustomerStates.WFB):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "OCZEKUJE NA RACHUNEK")

        elif (self._state == CustomerStates.TB):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "BIERZE RACHUNEK O WARTOSCI:", totalPrice)

        elif (self._state == CustomerStates.WFPB):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "OCZEKUJE NA POBRANIE OPLATY")

        elif (self._state == CustomerStates.PB):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "PLACI RACHUNEK O WARTOSCI:", totalPrice)

        elif (self._state == CustomerStates.OUT):
            print("KLIENT:", self._ID, "Z GRUPY:", self._groupID, "SIEDZACY PRZY STOLIKU:", self._tableID, "ODCHODZI")