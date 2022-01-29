#include "Simulation.h"

#include "CustomerStates.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <ctime>

Simulation::Simulation(std::string simulation_parameters_file_name, std::string products_data_file_name)
{
    fileReader = new FileReader();

    std::vector<int> parameters = fileReader -> readSimulationParameters(simulation_parameters_file_name);
    std::vector<Product*> productsList = fileReader -> readProductsData(products_data_file_name);

    numberOfTables = parameters[0];
    numberOfWaiters = parameters[1];
    numberOfCustomers = parameters[2];
    startTimeHour = parameters[3];
    minutes = parameters[4];
    simulationStep = parameters[5];

    srand(time(NULL));

    simulatedPizzeria = new Pizzeria(numberOfTables, numberOfWaiters, numberOfCustomers, productsList); 
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
    delete fileReader;
    delete simulatedPizzeria;
}