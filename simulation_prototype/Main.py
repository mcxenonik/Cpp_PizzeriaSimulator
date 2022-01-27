import argparse
from CustomerStates import CustomerStates
from Pizzeria import Pizzeria
from time import ctime, sleep


def read_from_file(filename):
    with open(filename, "r") as file:
        parameters = []
        counter = 0

        for line in file:
            if (counter != 3):
                parameters.append(int(line.split("=")[1].replace("\n", "")))
            else:
                parameters.append(line.split("=")[1].replace("\n", ""))

            counter += 1

        p = parameters[3].split(";")

        par = []

        for ch in p:
            par.append(ch.split(","))

        come_times = []

        for z in par:
            come_times.append((int(z[0]), int(z[1])))

    parameters[3] = come_times

    return parameters


def setSimulationParameters(filename):
    parameters = read_from_file(filename)

    numOfTables = parameters[0]
    numOfWaiters = parameters[1]
    numOfCustomers = parameters[2]

    come_times = parameters[3]
    print(come_times)

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
    parser = argparse.ArgumentParser(description="Pizzeria Simulation")
    parser.add_argument("filename", help="Name of file to load")
    args = parser.parse_args()

    numOfTables, numOfWaiters, numOfCustomers, come_times, startTime, minutes, step, run_sim, end_list = setSimulationParameters(args.filename)

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
