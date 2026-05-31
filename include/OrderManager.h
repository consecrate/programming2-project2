#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include "Order.h"

#include <vector>

class Cart;
class ProductManager;

class OrderManager {
private:
    std::vector<Order> orders;
    int nextOrderId;

public:
    OrderManager();

    Order createOrder(int customerId, Cart& cart, ProductManager& productManager);
    void addOrder(const Order& order);
    std::vector<Order> getOrdersByCustomerId(int customerId) const;
    const std::vector<Order>& getAllOrders() const;
    int generateOrderId();
    void displayOrdersByCustomerId(int customerId) const;
};

#endif
