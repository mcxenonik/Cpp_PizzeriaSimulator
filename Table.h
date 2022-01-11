#include <list>

class Table
{
    private:
        int ID;
        unsigned int size;
        bool isFull;
        int *groupID;
        std::list<int> customersIDList;

    public:
        Table(int new_id, unsigned int new_size);
        int getID();
        unsigned int getSize();
        bool getIsFull();
        int getGroupID();
        std::list<int> getCustomersIDList();
        void addCustomerToTable(int customerID, int customerGroupID);
        void deleteCustomerFromTable(int customerID);
        ~Table();
};