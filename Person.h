#ifndef PERSON_H
#define PERSON_H

#include "PersonInterface.h"

class Person : public PersonInterface
{
    protected: 
        int ID;
        std::string name;

    public:
        Person(int new_id, std::string new_name);

        int getID();
        std::string getName();
    
        virtual ~Person() {}
};
    
#endif