#ifndef PERSON_INTERFACE_H
#define PERSON_INTERFACE_H

#include <string>

class PersonInterface
{
    public:
        virtual int getID() = 0;
        virtual std::string getName() = 0;
};

#endif