#include "Pizzeria.h"

Pizzeria::Pizzeria(int numOfTables, int numOfWaiters, int numOfCustomers)
{
    menu = new Menu();

    for(int i = 0; i < numOfTables; i++)
        addTable();

    for(int i = 0; i < numOfWaiters; i++)
        addWaiter();
    
    for(int i = 0; i < numOfCustomers; i++)
        addCustomer();
}

std::vector<Person*>* Pizzeria::getWaiterList(){
    return &waiterList;
}

std::vector<Person*>* Pizzeria::getCustomerList(){
    return &customerList;
}

std::vector<Table*>* Pizzeria::getTableList(){
    return &tableList;
}

std::vector<Order*>* Pizzeria::getOrdersList(){
    return &orderList;
}

void Pizzeria::addWaiter(){
    Waiter* new_waiter = new Waiter(waiterList.size(), "SimpleWaiterName", menu);

    waiterList.push_back(new_waiter);
}

void Pizzeria::addCustomer(){
    Customer* new_customer = new Customer(customerList.size(), "SimpleCustomerName", (rand() % 5) + 1);

    customerList.push_back(new_customer);
}

void Pizzeria::addTable(){
    Table* new_table = new Table(tableList.size(), (rand() % 5) + 1);

    tableList.push_back(new_table);
}

int Pizzeria::addOrder(int customerID, int waiterID, std::vector<Product*> productList){
    Order* new_order = new Order(orderList.size(), customerID, waiterID, productList);

    orderList.push_back(new_order);

    return new_order -> getID();
}

void Pizzeria::decreaseOrdersTime(){
    std::cout << "****************************************************************************************" << std::endl;

    for(auto order : orderList)
    {
        if (order -> getIsReady() && !order -> getIsDelivered())
        {
            TaskPayload *payload = new TaskPayload();
            payload -> setOrder(order);

            Task* new_task = new Task(order -> getCustomerID(), TaskTypes::DO, payload);
            findMinTaskWaiter()-> addTask(new_task);
            order -> setIsDelivered(true);
        }
        else if (!order -> getIsReady()) 
        {
            order -> decreaseWaitTime();
        }
        

        std::cout << "ORDER ID: " << order -> getID() << " CUS ID: " << order -> getCustomerID() << 
                     " WAITTIME: " << order -> getWaitTime() << " IS READY: " << order -> getIsReady() << 
                     " IS DELIVERED: " << order -> getIsDelivered() << std::endl;
    }
    std::cout << "****************************************************************************************" << std::endl;

}

Person* Pizzeria::findMinTaskWaiter(){
    int min_tasks = waiterList[0] -> getNumberOfTasks();
    int waiterID = waiterList[0] -> getID();

    for(auto waiter : waiterList){
        if (waiter -> getNumberOfTasks() < min_tasks){
            min_tasks = waiter -> getNumberOfTasks();
            waiterID = waiter -> getID();
        }
    }

    return waiterList[waiterID];
}

Pizzeria::~Pizzeria() 
{
    for(auto waiter_ptr : waiterList)
    {
        delete waiter_ptr;
    }

    for(auto customer_ptr : customerList)
    {
        delete customer_ptr;
    }

    for(auto table_ptr : tableList)
    {
        delete table_ptr;
    }

    for(auto order_ptr : orderList)
    {
        delete order_ptr;
    }

    delete menu;
}