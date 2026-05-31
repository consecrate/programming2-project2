#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Interaction.h"
#include <vector>

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
    void showMenu(ProductManager& productManager,
                  StatisticsManager& statisticsManager,
                  OrderManager& orderManager,
                  const std::vector<Interaction>& interactions);
    void addProduct(ProductManager& productManager);
    void editProduct(ProductManager& productManager);
    void deleteProduct(ProductManager& productManager);
    void viewStatistics(StatisticsManager& statisticsManager,
                        ProductManager& productManager,
                        OrderManager& orderManager);
    void viewStatistics(StatisticsManager& statisticsManager,
                        ProductManager& productManager,
                        OrderManager& orderManager,
                        const std::vector<Interaction>& interactions);
};

#endif
