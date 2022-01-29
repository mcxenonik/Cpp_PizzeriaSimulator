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

        int startTime;
        int minutes;
        int step;

    public:
        Simulation(std::string filename);

        void runSimulation();

        ~Simulation();

};

#endif