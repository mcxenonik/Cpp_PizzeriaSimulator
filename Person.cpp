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

void Person::addTask(Task* new_task) {}

void Person::doTask(std::vector<Person*>* newPersonList, std::vector<Order*>* newOrderList) {}

void Person::setState(CustomerStates customerState) {}

CustomerStates Person::getState() { return CustomerStates::NEW; }

void Person::doAction(std::vector<Person*>* newPersonList, std::vector<Table*>* newTableList, std::vector<Order*>* newOrderList) {}

void Person::setOrderID(int newOrderId) {}

void Person::setMenu(Menu* new_menu) {}
