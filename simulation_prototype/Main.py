from CustomerStates import CustomerStates
from Pizzeria import Pizzeria
from time import ctime, sleep


def setSimulationParameters():
    numOfTables = 5
    numOfWaiters = 4
    numOfCustomers = 30

    come_times = [(8, 4), (8, 8), (8, 12), (8, 18), (8, 30), (8, 32), (8, 34), (8, 40), (8, 46), (8, 50)]

    startTime = 8
    minutes = 0
    step = 2

    run_sim = True
    end_list = []

    parameters = (numOfTables, numOfWaiters, 
                  numOfCustomers, come_times,
                  startTime, minutes, step, 
                  run_sim, end_list)

    return parameters


def formatTime(startTime, minutes):
    if (minutes >= 60):
        minutes -= 60
        startTime += 1

    if (len(str(minutes)) == 1):
        min = "0" + str(minutes)
        hour = str(startTime)
    else:
        min = str(minutes)
        hour = str(startTime)

    return hour, min, startTime, minutes


if __name__ == "__main__":
    numOfTables, numOfWaiters, numOfCustomers, come_times, startTime, minutes, step, run_sim, end_list = setSimulationParameters()

    sim_pizzeria = Pizzeria(numOfTables, numOfWaiters, numOfCustomers)

    print("START:", str(startTime) + ":" + str(minutes))

    while(run_sim):
        if (len(end_list) == len(sim_pizzeria.getCustomersList()) and (startTime, minutes) > come_times[0]):
            run_sim = False

        if ((startTime, minutes) in come_times):
            sim_pizzeria.addCustomer()
            print("PRZYCHODZI NOWY KLIENT:", sim_pizzeria.getCustomersList()[-1].getID(), "Z GRUPY:", sim_pizzeria.getCustomersList()[-1].getGroupID())

        for customer in sim_pizzeria.getCustomersList():
            customer.doAction(sim_pizzeria)

            if(customer.getState() == CustomerStates.OUT and customer.getID() not in end_list):
                end_list.append(customer.getID())

        print("----------------------------------------------------------------------------------------")

        for waiter in sim_pizzeria.getWaitersList():
            waiter.doTask(sim_pizzeria)

        sim_pizzeria.decreaseOrdersTime()

        minutes += step
        hour, min, startTime, minutes = formatTime(startTime, minutes)
        print("========================================================================================")
        print("CZAS:", hour + ":" + min)
        print("WYSZLO KLIENTOW:", len(end_list))
        print("========================================================================================")
        if (not run_sim):
            print("END SIMULATION")
            print("---STATYSTYKI---")
            print("ZAROBIONO:", sim_pizzeria.countMoney())
            print("---")
            sim_pizzeria.countMinMaxCustomerWaitingTime()
            sim_pizzeria.countMinMaxWaiterTasksDone()
            sim_pizzeria.countMinMaxWaiterValueOfCollectedOrdersStat()
        sleep(step)
