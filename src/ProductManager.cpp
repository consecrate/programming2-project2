#include "ProductManager.h"
#include "Utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>

std::vector<Product>& ProductManager::getProducts() { return products; }
const std::vector<Product>& ProductManager::getProducts() const { return products; }

Product* ProductManager::findProductById(int id) {
    for (auto& product : products) {
        if (product.getId() == id) return &product;
    }
    return nullptr;
}

const Product* ProductManager::findProductById(int id) const {
    for (const auto& product : products) {
        if (product.getId() == id) return &product;
    }
    return nullptr;
}

bool ProductManager::productExists(int id) const {
    return findProductById(id) != nullptr;
}

void ProductManager::addProduct(const Product& product) {
    if (productExists(product.getId())) {
        std::cout << "Product ID already exists. Product was not added.\n";
        return;
    }
    products.push_back(product);
}

bool ProductManager::editProduct(int id) {
    Product* product = findProductById(id);
    if (product == nullptr) {
        std::cout << "Product not found.\n";
        return false;
    }

    int choice;
    do {
        std::cout << "\nEditing product:\n";
        product->displayDetails();
        std::cout << "\n1. Edit name\n"
                  << "2. Edit category\n"
                  << "3. Edit price\n"
                  << "4. Edit stock quantity\n"
                  << "0. Finish editing\n";
        choice = getValidatedInt("Choose an option: ");

        if (choice == 1) {
            std::string name;
            std::cout << "Enter new name: ";
            std::getline(std::cin, name);
            name = trim(name);
            if (!name.empty()) product->setName(name);
        } else if (choice == 2) {
            std::string category;
            std::cout << "Enter new category: ";
            std::getline(std::cin, category);
            category = trim(category);
            if (!category.empty()) product->setCategory(category);
        } else if (choice == 3) {
            double price = getValidatedDouble("Enter new price: ");
            if (price < 0) std::cout << "Price cannot be negative.\n";
            else product->setPrice(price);
        } else if (choice == 4) {
            int stock = getValidatedInt("Enter new stock quantity: ");
            if (stock < 0) std::cout << "Stock cannot be negative.\n";
            else product->setStock(stock);
        } else if (choice != 0) {
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    std::cout << "Product updated successfully.\n";
    return true;
}

bool ProductManager::deleteProduct(int id) {
    auto it = std::remove_if(products.begin(), products.end(),
                             [id](const Product& product) { return product.getId() == id; });
    if (it == products.end()) {
        std::cout << "Product not found.\n";
        return false;
    }
    products.erase(it, products.end());
    std::cout << "Product deleted successfully.\n";
    return true;
}

void ProductManager::displayAllProducts() const {
    if (products.empty()) {
        std::cout << "No products available.\n";
        return;
    }

    std::cout << std::left
              << std::setw(5) << "ID"
              << std::setw(28) << "Name"
              << std::setw(18) << "Category"
              << std::right << std::setw(10) << "Price"
              << std::setw(10) << "Stock"
              << std::setw(10) << "Views"
              << std::setw(12) << "Purchases" << '\n';
    std::cout << std::string(93, '-') << '\n';
    for (const auto& product : products) {
        product.displaySummary();
    }
}

void ProductManager::displayProductsByCategory(std::string category) const {
    bool found = false;
    std::string wanted = trim(category);
    for (const auto& product : products) {
        if (product.getCategory() == wanted) {
            if (!found) {
                std::cout << "Products in category: " << wanted << "\n";
                std::cout << std::left
                          << std::setw(5) << "ID"
                          << std::setw(28) << "Name"
                          << std::setw(18) << "Category"
                          << std::right << std::setw(10) << "Price"
                          << std::setw(10) << "Stock"
                          << std::setw(10) << "Views"
                          << std::setw(12) << "Purchases" << '\n';
                std::cout << std::string(93, '-') << '\n';
            }
            product.displaySummary();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No products found in this category.\n";
    }
}