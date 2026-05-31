#include "Order.h"

#include <iomanip>
#include <iostream>

Order::Order() : orderId(0), customerId(0), totalPrice(0.0), dateTime("") {}

Order::Order(int orderId, int customerId, std::vector<OrderItem> items, double totalPrice, std::string dateTime)
    : orderId(orderId), customerId(customerId), items(items), totalPrice(totalPrice), dateTime(dateTime) {}

int Order::getOrderId() const { return orderId; }
int Order::getCustomerId() const { return customerId; }
double Order::getTotalPrice() const { return totalPrice; }
std::string Order::getDateTime() const { return dateTime; }
std::vector<OrderItem> Order::getItems() const { return items; }

void Order::displayOrder() const {
    std::cout << "\nOrder #" << orderId << " | Customer ID: " << customerId
              << " | Date: " << dateTime << '\n';
    std::cout << std::left << std::setw(6) << "ID" << std::setw(28) << "Product"
              << std::right << std::setw(10) << "Price" << std::setw(10) << "Qty"
              << std::setw(12) << "Subtotal" << '\n';
    for (const auto& item : items) {
        std::cout << std::left << std::setw(6) << item.getProductId()
                  << std::setw(28) << item.getProductName()
                  << std::right << std::fixed << std::setprecision(2)
                  << std::setw(10) << item.getPriceAtPurchase()
                  << std::setw(10) << item.getQuantity()
                  << std::setw(12) << item.getSubtotal() << '\n';
    }
    std::cout << "Total: " << std::fixed << std::setprecision(2) << totalPrice << "\n";
}