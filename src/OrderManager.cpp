#include "OrderManager.h"
#include "Cart.h"
#include "Product.h"
#include "ProductManager.h"
#include "Utils.h"

#include <iostream>

OrderManager::OrderManager() : nextOrderId(1) {}

Order OrderManager::createOrder(int customerId, Cart& cart, ProductManager& productManager) {
    std::vector<OrderItem> orderItems;
    double total = 0.0;

    if (cart.isEmpty()) {
        std::cout << "Cannot checkout because cart is empty.\n";
        return Order();
    }
    if (cart.hasMissingProducts(productManager)) {
        std::cout << "Cannot checkout because the cart contains unavailable products.\n";
        return Order();
    }

    for (const auto& cartItem : cart.getItems()) {
        Product* product = productManager.findProductById(cartItem.getProductId());
        if (product == nullptr) {
            std::cout << "Product ID " << cartItem.getProductId() << " does not exist.\n";
            return Order();
        }
        if (cartItem.getQuantity() <= 0 || cartItem.getQuantity() > product->getStock()) {
            std::cout << "Insufficient stock for " << product->getName() << ".\n";
            return Order();
        }
    }

    for (const auto& cartItem : cart.getItems()) {
        Product* product = productManager.findProductById(cartItem.getProductId());
        double subtotal = product->getPrice() * cartItem.getQuantity();
        total += subtotal;
        orderItems.push_back(OrderItem(product->getId(), product->getName(), product->getPrice(), cartItem.getQuantity()));
        product->reduceStock(cartItem.getQuantity());
        product->incrementPurchaseCount(cartItem.getQuantity());
    }

    Order order(generateOrderId(), customerId, orderItems, total, getCurrentDateTime());
    addOrder(order);
    cart.clear();
    return order;
}

void OrderManager::addOrder(const Order& order) {
    if (order.getOrderId() <= 0) return;
    orders.push_back(order);
    if (order.getOrderId() >= nextOrderId) {
        nextOrderId = order.getOrderId() + 1;
    }
}

std::vector<Order> OrderManager::getOrdersByCustomerId(int customerId) const {
    std::vector<Order> result;
    for (const auto& order : orders) {
        if (order.getCustomerId() == customerId) {
            result.push_back(order);
        }
    }
    return result;
}

const std::vector<Order>& OrderManager::getAllOrders() const { return orders; }

int OrderManager::generateOrderId() { return nextOrderId++; }

void OrderManager::displayOrdersByCustomerId(int customerId) const {
    auto customerOrders = getOrdersByCustomerId(customerId);
    if (customerOrders.empty()) {
        std::cout << "No orders found for this customer.\n";
        return;
    }
    for (const auto& order : customerOrders) {
        order.displayOrder();
    }
}
