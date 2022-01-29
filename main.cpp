#include "Simulation.h"

int main()
{
    std::string filename;
    Simulation* newSimulation = new Simulation(filename);

    newSimulation -> runSimulation();

    delete newSimulation;

    return 0;
}
