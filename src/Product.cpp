#include "Product.h"

#include <iomanip>
#include <iostream>

Product::Product()
    : id(0), name(""), category(""), price(0.0), stock(0), viewCount(0), purchaseCount(0) {}

Product::Product(int id, std::string name, std::string category, double price, int stock)
    : id(id), name(name), category(category),
      price(price >= 0 ? price : 0.0),
      stock(stock >= 0 ? stock : 0),
      viewCount(0), purchaseCount(0) {}

Product::Product(int id, std::string name, std::string category, double price, int stock,
                 int viewCount, int purchaseCount)
    : id(id), name(name), category(category),
      price(price >= 0 ? price : 0.0),
      stock(stock >= 0 ? stock : 0),
      viewCount(viewCount >= 0 ? viewCount : 0),
      purchaseCount(purchaseCount >= 0 ? purchaseCount : 0) {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }
int Product::getViewCount() const { return viewCount; }
int Product::getPurchaseCount() const { return purchaseCount; }

void Product::setName(std::string name) { this->name = name; }
void Product::setCategory(std::string category) { this->category = category; }
void Product::setPrice(double price) { if (price >= 0) this->price = price; }
void Product::setStock(int stock) { if (stock >= 0) this->stock = stock; }
void Product::setViewCount(int viewCount) { if (viewCount >= 0) this->viewCount = viewCount; }
void Product::setPurchaseCount(int purchaseCount) { if (purchaseCount >= 0) this->purchaseCount = purchaseCount; }

void Product::incrementViewCount() { ++viewCount; }

void Product::incrementPurchaseCount(int quantity) {
    if (quantity > 0) purchaseCount += quantity;
}

void Product::reduceStock(int quantity) {
    if (quantity > 0 && quantity <= stock) stock -= quantity;
}

void Product::displaySummary() const {
    std::cout << std::left
              << std::setw(5) << id
              << std::setw(28) << name
              << std::setw(18) << category
              << std::right << std::setw(10) << std::fixed << std::setprecision(2) << price
              << std::setw(10) << stock
              << std::setw(10) << viewCount
              << std::setw(12) << purchaseCount << '\n';
}

void Product::displayDetails() const {
    std::cout << "\nProduct ID: " << id << '\n'
              << "Name: " << name << '\n'
              << "Category: " << category << '\n'
              << "Price: " << std::fixed << std::setprecision(2) << price << '\n'
              << "Stock: " << stock << '\n'
              << "Views: " << viewCount << '\n'
              << "Purchases: " << purchaseCount << "\n";
}