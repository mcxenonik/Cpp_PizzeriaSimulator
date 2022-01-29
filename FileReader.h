#ifndef FILE_READER_H
#define FILE_READER_H

#include "Product.h"

#include <string>
#include <vector>

class FileReader
{
    private:

    public:
        FileReader();

        std::vector<int> readSimulationParameters(std::string simulation_parameters_file_name);
        std::vector<Product*> readProductsData(std::string products_data_file_name);

        ~FileReader();

};

#endif