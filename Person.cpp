#include "Person.h"

Person::Person(int new_id, std::string new_name)
{
    ID = new_id;
    name = new_name;
}

int Person::getID()
{
    return ID;
}

std::string Person::getName()
{
    return name;
}

