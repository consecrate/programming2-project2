#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include <string>

class OrderItem {
private:
    int productId;
    std::string productName;
    double priceAtPurchase;
    int quantity;

public:
    OrderItem();
    OrderItem(int productId, std::string productName, double priceAtPurchase, int quantity);

    int getProductId() const;
    std::string getProductName() const;
    double getPriceAtPurchase() const;
    int getQuantity() const;
    double getSubtotal() const;
};

#endif
