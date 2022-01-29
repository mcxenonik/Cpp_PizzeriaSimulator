#include "Simulation.h"

#include "CustomerStates.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <ctime>

Simulation::Simulation(std::string simulation_parameters_file_name, std::string products_data_file_name)
{
    std::ifstream filestream(simulation_parameters_file_name);

    std::string parameter_name;
    int parameter_value;

    while (filestream >> parameter_name >> parameter_value)
    {
        if (parameter_name == "numberOfTables")
        {
            numberOfTables = parameter_value;
        }
        else if (parameter_name == "numberOfWaiters")
        {
            numberOfWaiters = parameter_value;
        }
        else if (parameter_name == "numberOfCustomers")
        {
            numberOfCustomers = parameter_value;
        }
        else if (parameter_name == "startTimeHour")
        {
            startTimeHour = parameter_value;
        }
        else if (parameter_name == "minutes")
        {
            minutes = parameter_value;
        }
        else if (parameter_name == "simulationStep")
        {
            simulationStep = parameter_value;
        }
            
    };

    srand(time(NULL));

    simulatedPizzeria = new Pizzeria(numberOfTables, numberOfWaiters, numberOfCustomers, products_data_file_name); 
}

void Simulation::runSimulation()
{
    bool run_sim = true;
    std::vector<int> end_list;

    std::cout << "START SIMULATION" << std::endl << startTimeHour << ":" << minutes << std::endl;
    std::cout << "========================================================================================" << std::endl;

    while(run_sim)
    {
        if (end_list.size() == simulatedPizzeria -> getCustomerList() -> size())
        {
            run_sim = false;
        }

        for (auto customer_ptr : *(simulatedPizzeria -> getCustomerList()))
        {
            customer_ptr -> doAction(simulatedPizzeria -> getWaiterList(), simulatedPizzeria -> getTableList());

            if(customer_ptr -> getState() == CustomerStates::OUT && std::find(end_list.begin(), end_list.end(), customer_ptr -> getID()) == end_list.end())
            {
                end_list.push_back(customer_ptr -> getID());
            }
        }

        std::cout << "----------------------------------------------------------------------------------------" << std::endl;

        for (auto waiter_ptr : *(simulatedPizzeria -> getWaiterList()))
        {
            waiter_ptr -> doTask(simulatedPizzeria -> getCustomerList(), simulatedPizzeria -> getOrdersList());
        }

        simulatedPizzeria -> decreaseOrdersTime();


        minutes += simulationStep;

        if (minutes >= 60)
        {
            minutes -= 60;
            startTimeHour += 1;
        }

        std::cout << "========================================================================================" << std::endl;
        std::cout << "CZAS: " << startTimeHour << ":" << minutes << std::endl << "WYSZLO KLIENTOW: " << end_list.size() << std::endl;
        std::cout << "========================================================================================" << std::endl;
        
        if (!run_sim)
        {
            std::cout << "END SIMULATION" << std::endl;
            // std::cout << "---STATYSTYKI---" << std::endl;
            // std::cout << "ZAROBIONO:" << simulatedPizzeria -> countMoney() << std::endl;
            // std::cout << "---" << std::endl;
            // simulatedPizzeria -> countMinMaxCustomerWaitingTime();
            // simulatedPizzeria -> countMinMaxWaiterTasksDone();
            // simulatedPizzeria -> countMinMaxWaiterValueOfCollectedOrdersStat();
        }

        sleep(simulationStep);
    };
}

Simulation::~Simulation()
{
    delete simulatedPizzeria;
}