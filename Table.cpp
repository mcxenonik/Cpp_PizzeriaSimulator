#include "Table.h"

Table::Table(int new_id, unsigned int new_size)
{
    ID = new_id;
    size = new_size;
    isFull = false;
    groupID = nullptr;
}

int Table::getID()
{
    return ID;
}

unsigned int Table::getSize()
{
    return size;
}

bool Table::getIsFull()
{
    return isFull;
}

int Table::getGroupID()
{
    return *groupID;
}

std::list<int> Table::getCustomersIDList()
{
    return customersIDList;
}

void Table::addCustomerToTable(int customerID, int customerGroupID)
{
    customersIDList.push_back(customerID);

    if (groupID == nullptr)
    {
        groupID = new int;
        *groupID = customerGroupID;
    }

    if (customersIDList.size() == size)
    {
        isFull = true;
    }
}

void Table::deleteCustomerFromTable(int customerID)
{
    customersIDList.remove(customerID);
    isFull = false;

    if (customersIDList.size() == 0)
    {
        groupID = nullptr;
    }
}

Table::~Table()
{
    delete groupID;
}