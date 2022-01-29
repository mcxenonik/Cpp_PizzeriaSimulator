#ifndef SIMULATION_H
#define SIMULATION_H

#include "Pizzeria.h"
#include "FileReader.h"

#include <string>

class Simulation
{
    private:
        Pizzeria* simulatedPizzeria;
        FileReader* fileReader;

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