#include "Simulation.h"

#include "CustomerStates.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <ctime>

Simulation::Simulation(std::string simulation_parameters_file_name, std::string products_data_file_name)
{
    fileReader = new FileReader();

    std::vector<int> parameters;
    std::vector<Product*> productsList;

    try
    {
        parameters = fileReader -> readSimulationParameters(simulation_parameters_file_name);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Simulation parameters load failed!";
        exit(1);
    }

    try
    {
        productsList = fileReader -> readProductsData(products_data_file_name);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Products data load failed!";
        exit(1);
    }

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
    int end_counter;

    std::cout << "START SIMULATION" << std::endl << startTimeHour << ":" << minutes << std::endl;
    std::cout << "========================================================================================" << std::endl;

    while(run_sim)
    {
        if (end_counter == static_cast<int>(simulatedPizzeria -> getCustomerList() -> size()))
        {
            run_sim = false;
        }
        
        end_counter = simulatedPizzeria -> simulateCustomers();

        std::cout << "----------------------------------------------------------------------------------------" << std::endl;

        simulatedPizzeria -> simulateWaiters();

        std::cout << "****************************************************************************************" << std::endl;

        simulatedPizzeria -> decreaseOrdersTime();

        std::cout << "****************************************************************************************" << std::endl;


        minutes += simulationStep;

        if (minutes >= 60)
        {
            minutes -= 60;
            startTimeHour += 1;
        }

        std::cout << "========================================================================================" << std::endl;
        std::cout << "CZAS: " << startTimeHour << ":" << minutes << std::endl << "WYSZLO KLIENTOW: " << end_counter << std::endl;
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