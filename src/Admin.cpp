#include "Admin.h"
#include "OrderManager.h"
#include "Product.h"
#include "ProductManager.h"
#include "StatisticsManager.h"
#include "Utils.h"

#include <iostream>

Admin::Admin() : User() {}

Admin::Admin(int userId, std::string name, std::string email, std::string password)
    : User(userId, name, email, password, "admin") {}

void Admin::showMenu(ProductManager& productManager,
                     StatisticsManager& statisticsManager,
                     OrderManager& orderManager) {
    std::vector<Interaction> noInteractions;
    showMenu(productManager, statisticsManager, orderManager, noInteractions);
}

void Admin::showMenu(ProductManager& productManager,
                     StatisticsManager& statisticsManager,
                     OrderManager& orderManager,
                     const std::vector<Interaction>& interactions) {
    int choice;
    do {
        std::cout << "\n===== Admin Menu =====\n"
                  << "1. View all products\n"
                  << "2. Add product\n"
                  << "3. Edit product\n"
                  << "4. Delete product\n"
                  << "5. View statistics\n"
                  << "0. Logout\n";
        choice = getValidatedInt("Choose an option: ");

        switch (choice) {
            case 1:
                productManager.displayAllProducts();
                break;
            case 2:
                addProduct(productManager);
                break;
            case 3:
                editProduct(productManager);
                break;
            case 4:
                deleteProduct(productManager);
                break;
            case 5:
                viewStatistics(statisticsManager, productManager, orderManager, interactions);
                break;
            case 0:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    } while (choice != 0);
}

void Admin::addProduct(ProductManager& productManager) {
    std::cout << "\n===== Add New Product =====\n";
    int id = getValidatedInt("Product ID: ");
    if (productManager.productExists(id)) {
        std::cout << "A product with this ID already exists.\n";
        return;
    }

    std::string name;
    std::cout << "Name: ";
    std::getline(std::cin, name);
    name = trim(name);

    std::string category;
    std::cout << "Category: ";
    std::getline(std::cin, category);
    category = trim(category);

    double price = getValidatedDouble("Price: ");
    int stock = getValidatedInt("Stock quantity: ");

    if (name.empty() || category.empty()) {
        std::cout << "Name and category cannot be empty.\n";
        return;
    }
    if (price < 0 || stock < 0) {
        std::cout << "Price and stock cannot be negative.\n";
        return;
    }

    productManager.addProduct(Product(id, name, category, price, stock));
    std::cout << "Product added successfully.\n";
}

void Admin::editProduct(ProductManager& productManager) {
    int id = getValidatedInt("Enter product ID to edit: ");
    productManager.editProduct(id);
}

void Admin::deleteProduct(ProductManager& productManager) {
    int id = getValidatedInt("Enter product ID to delete: ");
    Product* product = productManager.findProductById(id);
    if (product == nullptr) {
        std::cout << "Product not found.\n";
        return;
    }

    product->displayDetails();
    std::cout << "Delete this product? (y/n): ";
    std::string answer;
    std::getline(std::cin, answer);
    if (!answer.empty() && (answer[0] == 'y' || answer[0] == 'Y')) {
        productManager.deleteProduct(id);
    } else {
        std::cout << "Delete cancelled.\n";
    }
}

void Admin::viewStatistics(StatisticsManager& statisticsManager,
                           ProductManager& productManager,
                           OrderManager& orderManager) {
    std::vector<Interaction> noInteractions;
    viewStatistics(statisticsManager, productManager, orderManager, noInteractions);
}

void Admin::viewStatistics(StatisticsManager& statisticsManager,
                           ProductManager& productManager,
                           OrderManager& orderManager,
                           const std::vector<Interaction>& interactions) {
    (void)orderManager;
    int choice;
    do {
        std::cout << "\n===== Statistics =====\n"
                  << "1. Most viewed products\n"
                  << "2. Best-selling products\n"
                  << "3. Active users\n"
                  << "4. Show all statistics\n"
                  << "0. Back\n";
        choice = getValidatedInt("Choose an option: ");

        int limit = 5;
        switch (choice) {
            case 1:
                limit = getValidatedInt("How many products to show? ");
                statisticsManager.displayMostViewedProducts(productManager.getProducts(), limit);
                break;
            case 2:
                limit = getValidatedInt("How many products to show? ");
                statisticsManager.displayBestSellingProducts(productManager.getProducts(), limit);
                break;
            case 3:
                limit = getValidatedInt("How many users to show? ");
                statisticsManager.displayActiveUsers(interactions, limit);
                break;
            case 4:
                statisticsManager.displayMostViewedProducts(productManager.getProducts(), 5);
                statisticsManager.displayBestSellingProducts(productManager.getProducts(), 5);
                statisticsManager.displayActiveUsers(interactions, 5);
                break;
            case 0:
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    } while (choice != 0);
}