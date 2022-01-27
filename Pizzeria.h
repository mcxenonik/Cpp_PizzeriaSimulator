#ifndef PIZZERIA_H
#define PIZZERIA_H

#include "Waiter.h"
#include "Customer.h"
#include "Table.h"
#include "Order.h"
#include "Menu.h"

#include <vector>

class Pizzeria
{
    private:
        std::vector<Waiter*> waiterList;
        std::vector<Customer*> customerList;
        std::vector<Table*> tableList;
        std::vector<Order*> orderList;
        Menu* menu;

    public:
        Pizzeria(int numOfTables, int numOfWaiters, int numOfCustomers);

        std::vector<Waiter*> getWaiterList();
        std::vector<Customer*> getCustomerList();
        std::vector<Table*> getTableList();
        std::vector<Order*> getOrdersList();
        Menu* getMenu();

        Waiter* getWaiterByID(int waiterID);
        Customer* getCustomerByID(int customerID);
        Table* getTableByID(int tableID);
        Order* getOrderByID(int orderID);
        Product* getProductByID(int productID);
        
        void addWaiter();
        void addCustomer();
        void addTable();
        int addOrder(int customerID, int waiterID, std::vector<Product*> productList);
        void decreaseOrdersTime();
        int findMinTaskWaiter();

        ~Pizzeria();

};

#endif