#ifndef SIMULATION_H
#define SIMULATION_H

#include "Pizzeria.h"

#include <string>

class Simulation
{
    private:
        Pizzeria* simulatedPizzeria;

        int numberOfTables;
        int numberOfWaiters;
        int numberOfCustomers;

        int startTimeHour;
        int minutes;
        int simulationStep;

    public:
        Simulation(std::string simulation_parameters_file_name, std::string products_data_file_name);

        void runSimulation();

        ~Simulation();

};

#endif