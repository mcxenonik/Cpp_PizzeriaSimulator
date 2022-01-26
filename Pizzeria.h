#include "Waiter.h"
#include "Customer.h"
#include "Table.h"
#include "Order.h"
#include "Menu.h"
class Pizzeria
{
    private:
        std::vector<Waiter*> waitersList;
        std::vector<Customer*> customersList;
        std::vector<Table*> tablesList;
        std::vector<Order*> ordersList;
        Menu* menu;

    public:
        creatPizzeria(numOfTables, numOfWaiters, numOfCustomers);

        std::vector<Waiter*> getWaitersList();
        std::vector<Customer*> getCustomerList();
        std::vector<Table*> getTableList();
        std::vector<Order*> getOrdersList();
        Menu* getMenu();

        Waiter* getWaiterByID(waiterID);
        Customer* getCustomerByID(customerID);
        Table* getTableByID(TableID);
        Order* getOrderByID(OrderID);
        Product* getProductByID(ProductID);
        
        void addWaiter();
        void addCustomer();
        void addTable();
        int addOrder(customerID, waiterID, productList);
        void decreaseOrdersTime();
        int findMinTaskWaiter();

};