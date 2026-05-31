#include "Admin.h"
#include "Customer.h"
#include "FileManager.h"
#include "Interaction.h"
#include "OrderManager.h"
#include "ProductManager.h"
#include "RecommendationEngine.h"
#include "StatisticsManager.h"
#include "Utils.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {
    const std::string PRODUCT_FILE = "data/products.txt";
    const std::string USER_FILE = "data/users.txt";
    const std::string ORDER_FILE = "data/orders.txt";
    const std::string INTERACTION_FILE = "data/interactions.txt";

    int generateNextCustomerId(const std::vector<Customer>& customers, const std::vector<Admin>& admins) {
        int maxId = 0;
        for (const auto& customer : customers) maxId = std::max(maxId, customer.getUserId());
        for (const auto& admin : admins) maxId = std::max(maxId, admin.getUserId());
        return maxId + 1;
    }

    void syncCustomerHistory(Customer& customer, const std::vector<Interaction>& interactions) {
        for (const auto& interaction : interactions) {
            if (interaction.getCustomerId() == customer.getUserId()) {
                if (interaction.getType() == "view") customer.addViewedProductId(interaction.getProductId());
                else if (interaction.getType() == "purchase") customer.addPurchasedProductId(interaction.getProductId());
            }
        }
    }

    Customer* findCustomerByEmail(std::vector<Customer>& customers, const std::string& email) {
        for (auto& customer : customers) {
            if (customer.getEmail() == email) return &customer;
        }
        return nullptr;
    }

    Admin* findAdminByEmail(std::vector<Admin>& admins, const std::string& email) {
        for (auto& admin : admins) {
            if (admin.getEmail() == email) return &admin;
        }
        return nullptr;
    }

    const Admin* findAdminByEmail(const std::vector<Admin>& admins, const std::string& email) {
        for (const auto& admin : admins) {
            if (admin.getEmail() == email) return &admin;
        }
        return nullptr;
    }

    void registerCustomer(std::vector<Customer>& customers, const std::vector<Admin>& admins) {
        std::string name, email, password;
        std::cout << "Name: ";
        std::getline(std::cin, name);
        std::cout << "Email: ";
        std::getline(std::cin, email);
        std::cout << "Password: ";
        std::getline(std::cin, password);

        if (name.empty() || email.empty() || password.empty()) {
            std::cout << "Registration failed: fields cannot be empty.\n";
            return;
        }
        if (findCustomerByEmail(customers, email) != nullptr) {
            std::cout << "A customer with this email already exists.\n";
            return;
        }
        if (findAdminByEmail(admins, email) != nullptr) {
            std::cout << "A user with this email already exists.\n";
            return;
        }

        int id = generateNextCustomerId(customers, admins);
        customers.push_back(Customer(id, name, email, password));
        std::cout << "Registration successful. Your customer ID is " << id << ".\n";
    }
}

int main() {
    ProductManager productManager;
    OrderManager orderManager;
    RecommendationEngine recommendationEngine;
    StatisticsManager statisticsManager;
    FileManager fileManager;
    std::vector<Customer> customers;
    std::vector<Admin> admins;
    std::vector<Interaction> interactions;

    fileManager.loadProducts(productManager, PRODUCT_FILE);
    fileManager.loadUsers(customers, admins, USER_FILE);
    fileManager.loadOrders(orderManager, ORDER_FILE);
    fileManager.loadInteractions(interactions, INTERACTION_FILE);

    int choice;
    do {
        std::cout << "\n===== Smart E-Commerce System =====\n"
                  << "1. Login as customer\n"
                  << "2. Login as admin\n"
                  << "3. Register customer\n"
                  << "0. Save and exit\n";
        choice = getValidatedInt("Choose an option: ");

        if (choice == 1) {
            std::string email, password;
            std::cout << "Email: ";
            std::getline(std::cin, email);
            std::cout << "Password: ";
            std::getline(std::cin, password);
            Customer* customer = findCustomerByEmail(customers, email);
            if (customer != nullptr && customer->checkPassword(password)) {
                syncCustomerHistory(*customer, interactions);
                customer->showMenu(productManager, orderManager, recommendationEngine, fileManager, interactions);
            } else {
                std::cout << "Invalid customer email or password.\n";
            }
        } else if (choice == 2) {
            std::string email, password;
            std::cout << "Email: ";
            std::getline(std::cin, email);
            std::cout << "Password: ";
            std::getline(std::cin, password);
            Admin* admin = findAdminByEmail(admins, email);
            if (admin != nullptr && admin->checkPassword(password)) {
                admin->showMenu(productManager, statisticsManager, orderManager, interactions);
            } else {
                std::cout << "Invalid admin email or password.\n";
            }
        } else if (choice == 3) {
            registerCustomer(customers, admins);
        } else if (choice == 0) {
            fileManager.saveProducts(productManager, PRODUCT_FILE);
            fileManager.saveUsers(customers, admins, USER_FILE);
            fileManager.saveOrders(orderManager, ORDER_FILE);
            fileManager.saveInteractions(interactions, INTERACTION_FILE);
            std::cout << "Data saved. Goodbye!\n";
        } else {
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
