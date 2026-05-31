#include "FileManager.h"
#include "OrderManager.h"
#include "Product.h"
#include "ProductManager.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace {
    int toInt(const std::string& text, int fallback = 0) {
        try { return std::stoi(trim(text)); }
        catch (...) { return fallback; }
    }

    double toDouble(const std::string& text, double fallback = 0.0) {
        try { return std::stod(trim(text)); }
        catch (...) { return fallback; }
    }

    bool isIgnorableLine(const std::string& line) {
        std::string clean = trim(line);
        return clean.empty() || clean[0] == '#';
    }
}

void FileManager::loadProducts(ProductManager& productManager, std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Could not open " << filename << ". Starting with empty product list.\n";
        return;
    }

    productManager.getProducts().clear();
    std::string line;
    while (std::getline(file, line)) {
        if (isIgnorableLine(line)) continue;
        auto parts = split(line, '|');
        if (parts.size() < 7) continue;

        int id = toInt(parts[0]);
        std::string name = parts[1];
        std::string category = parts[2];
        double price = toDouble(parts[3]);
        int stock = toInt(parts[4]);
        int views = toInt(parts[5]);
        int purchases = toInt(parts[6]);

        if (id > 0 && !productManager.productExists(id)) {
            productManager.addProduct(Product(id, name, category, price, stock, views, purchases));
        }
    }
}

void FileManager::saveProducts(const ProductManager& productManager, std::string filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Could not save products to " << filename << ".\n";
        return;
    }

    for (const auto& product : productManager.getProducts()) {
        file << product.getId() << '|'
             << product.getName() << '|'
             << product.getCategory() << '|'
             << product.getPrice() << '|'
             << product.getStock() << '|'
             << product.getViewCount() << '|'
             << product.getPurchaseCount() << '\n';
    }
}

void FileManager::loadUsers(std::vector<Customer>& customers, std::vector<Admin>& admins, std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Could not open " << filename << ". Using default demo users.\n";
        customers.push_back(Customer(1, "Josh", "josh@email.com", "1234"));
        admins.push_back(Admin(2, "Admin", "admin@email.com", "admin123"));
        return;
    }

    customers.clear();
    admins.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (isIgnorableLine(line)) continue;
        auto parts = split(line, '|');
        if (parts.size() < 5) continue;

        int userId = toInt(parts[0]);
        std::string name = parts[1];
        std::string email = parts[2];
        std::string password = parts[3];
        std::string role = parts[4];

        if (role == "admin") {
            admins.push_back(Admin(userId, name, email, password));
        } else {
            customers.push_back(Customer(userId, name, email, password));
        }
    }

    if (customers.empty()) customers.push_back(Customer(1, "Josh", "josh@email.com", "1234"));
    if (admins.empty()) admins.push_back(Admin(2, "Admin", "admin@email.com", "admin123"));
}

void FileManager::saveUsers(const std::vector<Customer>& customers, const std::vector<Admin>& admins, std::string filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Could not save users to " << filename << ".\n";
        return;
    }

    for (const auto& customer : customers) {
        file << customer.getUserId() << '|'
             << customer.getName() << '|'
             << customer.getEmail() << '|'
             << customer.getPassword() << '|'
             << customer.getRole() << '\n';
    }
    for (const auto& admin : admins) {
        file << admin.getUserId() << '|'
             << admin.getName() << '|'
             << admin.getEmail() << '|'
             << admin.getPassword() << '|'
             << admin.getRole() << '\n';
    }
}

void FileManager::loadOrders(OrderManager& orderManager, std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (isIgnorableLine(line)) continue;
        auto parts = split(line, '|');
        if (parts.size() < 5) continue;

        int orderId = toInt(parts[0]);
        int customerId = toInt(parts[1]);
        std::string dateTime = parts[2];
        double totalPrice = toDouble(parts[3]);
        std::vector<OrderItem> items;

        auto rawItems = split(parts[4], ';');
        for (const auto& rawItem : rawItems) {
            auto itemParts = split(rawItem, ',');
            if (itemParts.size() < 4) continue;
            items.push_back(OrderItem(toInt(itemParts[0]), itemParts[1], toDouble(itemParts[2]), toInt(itemParts[3])));
        }

        if (orderId > 0) {
            orderManager.addOrder(Order(orderId, customerId, items, totalPrice, dateTime));
        }
    }
}

void FileManager::saveOrders(const OrderManager& orderManager, std::string filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Could not save orders to " << filename << ".\n";
        return;
    }

    for (const auto& order : orderManager.getAllOrders()) {
        file << order.getOrderId() << '|'
             << order.getCustomerId() << '|'
             << order.getDateTime() << '|'
             << order.getTotalPrice() << '|';

        auto items = order.getItems();
        for (size_t i = 0; i < items.size(); ++i) {
            file << items[i].getProductId() << ','
                 << items[i].getProductName() << ','
                 << items[i].getPriceAtPurchase() << ','
                 << items[i].getQuantity();
            if (i + 1 < items.size()) file << ';';
        }
        file << '\n';
    }
}

void FileManager::loadInteractions(std::vector<Interaction>& interactions, std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }

    interactions.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (isIgnorableLine(line)) continue;
        auto parts = split(line, '|');
        if (parts.size() < 4) continue;

        int customerId = toInt(parts[0]);
        int productId = toInt(parts[1]);
        std::string type = parts[2];
        int count = toInt(parts[3]);

        if (customerId > 0 && productId > 0 && count > 0 && (type == "view" || type == "purchase")) {
            interactions.push_back(Interaction(customerId, productId, type, count));
        }
    }
}

void FileManager::saveInteractions(const std::vector<Interaction>& interactions, std::string filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Could not save interactions to " << filename << ".\n";
        return;
    }

    for (const auto& interaction : interactions) {
        file << interaction.getCustomerId() << '|'
             << interaction.getProductId() << '|'
             << interaction.getType() << '|'
             << interaction.getCount() << '\n';
    }
}