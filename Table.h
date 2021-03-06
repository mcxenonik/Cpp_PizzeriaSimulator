#ifndef TABLE_H
#define TABLE_H

#include <list>

class Table
{
    private:
        int ID;
        unsigned int size;
        bool isFull;
        int groupID;
        std::list<int> customersIDList;

    public:
        Table(int new_id, unsigned int new_size);

        int getID();
        bool getIsFull();
        int getGroupID();

        void addCustomerToTable(int customerID, int customerGroupID);
        void deleteCustomerFromTable(int customerID);
        
        ~Table();
};

#endif