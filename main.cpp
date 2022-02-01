#include "Simulation.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Program parameters are incorrect!" << std::endl;
        std::cerr << "Usage: " << argv[0] << " simulation_parameters_file_name.txt " << "products_data_file_name.json" << std::endl;

        return 1;
    }
    
    Simulation* newSimulation = new Simulation(argv[1], argv[2]);

    newSimulation -> runSimulation();

    delete newSimulation;

    return 0;
}
