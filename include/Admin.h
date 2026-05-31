#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class OrderManager;
class ProductManager;
class StatisticsManager;

class Admin : public User {
public:
    Admin();
    Admin(int userId, std::string name, std::string email, std::string password);

    void showMenu(ProductManager& productManager,
                  StatisticsManager& statisticsManager,
                  OrderManager& orderManager);
    void addProduct(ProductManager& productManager);
    void editProduct(ProductManager& productManager);
    void deleteProduct(ProductManager& productManager);
    void viewStatistics(StatisticsManager& statisticsManager,
                        ProductManager& productManager,
                        OrderManager& orderManager);
};

#endif
