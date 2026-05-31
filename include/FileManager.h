#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Admin.h"
#include "Customer.h"
#include "Interaction.h"

#include <string>
#include <vector>

class OrderManager;
class ProductManager;

class FileManager {
public:
    void loadProducts(ProductManager& productManager, std::string filename);
    void saveProducts(const ProductManager& productManager, std::string filename);
    void loadUsers(std::vector<Customer>& customers, std::vector<Admin>& admins, std::string filename);
    void saveUsers(const std::vector<Customer>& customers, const std::vector<Admin>& admins, std::string filename);
    void loadOrders(OrderManager& orderManager, std::string filename);
    void saveOrders(const OrderManager& orderManager, std::string filename);
    void loadInteractions(std::vector<Interaction>& interactions, std::string filename);
    void saveInteractions(const std::vector<Interaction>& interactions, std::string filename);
};

#endif
