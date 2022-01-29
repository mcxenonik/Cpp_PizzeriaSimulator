#include "CustomerStates.h"
#include "Pizzeria.h"

#include <vector>
#include <algorithm>
#include <unistd.h>

int main()
{
    int numOfTables = 2;
    int numOfWaiters = 2;
    int numOfCustomers = 1;

    int startTime = 8;
    int minutes = 0;
    int step = 2;

    bool run_sim = true;
    std::vector<int> end_list;

    srand(time(NULL));

    Pizzeria *sim_pizzeria = new Pizzeria(numOfTables, numOfWaiters, numOfCustomers);

    std::cout << "START SIMULATION" << std::endl << startTime << ":" << minutes << std::endl;
    std::cout << "========================================================================================" << std::endl;

    while(run_sim)
    {
        if (end_list.size() == sim_pizzeria -> getCustomerList() -> size())
        {
            run_sim = false;
        }

        for (auto customer_ptr : *(sim_pizzeria -> getCustomerList()))
        {
            customer_ptr -> doAction(sim_pizzeria -> getWaiterList(), sim_pizzeria -> getTableList());

            if(customer_ptr -> getState() == CustomerStates::OUT && std::find(end_list.begin(), end_list.end(), customer_ptr -> getID()) == end_list.end())
            {
                end_list.push_back(customer_ptr -> getID());
            }
        }

        std::cout << "----------------------------------------------------------------------------------------" << std::endl;

        for (auto waiter_ptr : *(sim_pizzeria -> getWaiterList()))
        {
            waiter_ptr -> doTask(sim_pizzeria -> getCustomerList(), sim_pizzeria -> getOrdersList());
        }

        sim_pizzeria -> decreaseOrdersTime();


        minutes += step;

        if (minutes >= 60)
        {
            minutes -= 60;
            startTime += 1;
        }

        std::cout << "========================================================================================" << std::endl;
        std::cout << "CZAS: " << startTime << ":" << minutes << std::endl << "WYSZLO KLIENTOW: " << end_list.size() << std::endl;
        std::cout << "========================================================================================" << std::endl;
        
        if (!run_sim)
        {
            std::cout << "END SIMULATION" << std::endl;
            // std::cout << "---STATYSTYKI---" << std::endl;
            // std::cout << "ZAROBIONO:" << sim_pizzeria -> countMoney() << std::endl;
            // std::cout << "---" << std::endl;
            // sim_pizzeria -> countMinMaxCustomerWaitingTime();
            // sim_pizzeria -> countMinMaxWaiterTasksDone();
            // sim_pizzeria -> countMinMaxWaiterValueOfCollectedOrdersStat();
        }

        sleep(step);
    };

    delete sim_pizzeria;

    return 0;
}
