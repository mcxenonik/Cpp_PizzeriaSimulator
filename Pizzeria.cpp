#include "Pizzeria.h"

class Pizzeria
{
    Pizzeria::Pizzeria(int numOfTables, int numOfWaiters, int numOfCustomers){
        menu = Menu();

        for(int i=0; i<numOfTables; i++)
            addTable();

        for(int i=0; i<numOfWaiters; i++)
            addWaiter();
        
        for(int i=0; i<numOfCustomers; i++)
            addCustomer();
    };

    std::vector<Waiter*> Pizzeria::getWaitersList(){
        return waiterList;
    };

    std::vector<Customer*> Pizzeria::getCustomerList(){
        return customerList;
    };

    std::vector<Table*> Pizzeria::getTableList(){
        return tableList;
    };

    std::vector<Order*> Pizzeria::getOrdersList(){
        return ordersList;
    };

    Menu* Pizzeria::getMenu(){
        return menu;
    };

    Waiter* Pizzeria::getWaiterByID(int waiterID){
        return waitersList[waiterID];
    };

    Customer* Pizzeria::getCustomerByID(int customerID){
        return customersList[customerID];
    };

    Table* Pizzeria::getTableByID(int tableID){
        return tablesList[tableID];
    };

    Order* Pizzeria::getOrderByID(int orderID){
        return ordersList[orderID];
    };

    Product* Pizzeria::getProductByID(int productID){
        return menu[productID];
    };

    void Pizzeria::addWaiter(){
        Waiter* new_waiter = Waiter(waitersList.length());
        waitersList.append(new_waiter);
    };

    void Pizzeria::addCustomer(){
        Customer* new_customer = Customer(customersList.length(), rand() % 5);

        customersList.append(new_customer);
    };

    void Pizzeria::addTable(){
        Table* new_table = Table(tablesList.length(), (rand() % 5) + 1);

        tablesList.append(new_table);
    };

    int Pizzeria::addOrder(customerID, waiterID, productList){
        Order* new_order = Order(ordersList.length(), customerID, waiterID, productList);
        ordersList.append(new_order);

        return new_order.getID();
    };

    void Pizzeria::decreaseOrdersTime(){
        print("****************************************************************************************");
        for(auto order : ordersList){
            if (order->isReady() && !order->isDelivered()){
                Task* new_task = Task(order->getCustomerID(), TaskTypes.DO, order->getID());
                getWaiterByID(findMinTaskWaiter()).addTask(new_task);
                getOrderByID(order -> getID()) -> setIsDelivered(true);
            }
            else if (!order->isReady()) {
                order->decreaseWaitTime();
            }
            

            print("ORDER ID:", order->getID(), "CUS ID:", order->getCustomerID(), "WAITTIME:", order->getWaitTime(), "IS READY:", order->isReady(), "IS DELIVERED:", order->isDelivered());
        }
        print("****************************************************************************************");

    };

    int Pizzeria::findMinTaskWaiter(){
        int min_tasks = waitersList[0].getNumberOfTasks();
        int waiterID = waitersList[0].getID();

        for(auto waiter : waitersList){
            if (waiter->getNumberOfTasks() < min_tasks){
                min_tasks = waiter->getNumberOfTasks();
                waiterID = waiter->getID();
            }
        }
        return waiterID;
        
    };

};