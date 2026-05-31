#ifndef ORDER_H
#define ORDER_H

#include "OrderItem.h"

#include <string>
#include <vector>

class Order {
private:
    int orderId;
    int customerId;
    std::vector<OrderItem> items;
    double totalPrice;
    std::string dateTime;

public:
    Order();
    Order(int orderId, int customerId, std::vector<OrderItem> items, double totalPrice, std::string dateTime);

    int getOrderId() const;
    int getCustomerId() const;
    double getTotalPrice() const;
    std::string getDateTime() const;
    std::vector<OrderItem> getItems() const;
    void displayOrder() const;
};

#endif
