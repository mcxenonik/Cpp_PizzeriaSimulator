#include "Task.h"

#include <stdlib.h>

Task::Task(int new_customerID, TaskTypes new_taskType, TaskPayload *new_taskPayload)
{
    ID = rand() % 1000000;
    customerID = new_customerID;
    taskType = new_taskType;
    taskPayload = new_taskPayload;
}

int Task::getID()
{
    return ID;
}

int Task::getCustomerID()
{
    return customerID;
}

TaskTypes Task::getTaskType()
{
    return taskType;
}

TaskPayload* Task::getTaskPayload()
{
    return taskPayload;
}

Task::~Task()
{
    delete taskPayload;
}