#include "TaskTypes.h"
#include "TaskPayload.h"

class Task
{
    private:
        int ID;
        int customerID;
        TaskTypes taskType;
        TaskPayload taskPayload;
        
    public:
        Task(int new_customerID, TaskTypes new_taskType, TaskPayload new_taskPayload);

        int getID();
        int getCustomerID();
        TaskTypes getTaskType();
        TaskPayload getTaskPayload();
        
        ~Task();
};