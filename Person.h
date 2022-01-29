#ifndef PERSON_H
#define PERSON_H

#include "PersonInterface.h"
#include "Task.h"
#include "Order.h"
#include "CustomerStates.h"
#include "Table.h"
#include "Menu.h"

#include <vector>

class Person : public PersonInterface
{
    protected: 
        int ID;
        std::string name;

    public:
        Person(int new_id, std::string new_name);

        int getID();
        std::string getName();

        virtual ~Person();

        virtual int getNumberOfTasks();
        virtual void addTask(Task*);
        virtual void doTask(std::vector<Person*>*, std::vector<Order*>*);
        virtual void setState(CustomerStates);
        virtual CustomerStates getState();
        virtual void doAction(std::vector<Person*>*, std::vector<Table*>*);
        virtual void setOrder(Order*);
        virtual void setMenu(Menu*);
};
    
#endif