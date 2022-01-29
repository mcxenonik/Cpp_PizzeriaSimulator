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

Person::~Person() 
{

}

int Person::getNumberOfTasks() { return 0; }

void Person::addTask(Task*) {}

void Person::doTask(std::vector<Person*>*, std::vector<Order*>*) {}

void Person::setState(CustomerStates) {}

CustomerStates Person::getState() { return CustomerStates::NEW; }

void Person::doAction(std::vector<Person*>*, std::vector<Table*>*) {}

void Person::setOrder(Order*) {}

void Person::setMenu(Menu*) {}
