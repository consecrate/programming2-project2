#include "OrderItem.h"

OrderItem::OrderItem() : productId(0), productName(""), priceAtPurchase(0.0), quantity(0) {}

OrderItem::OrderItem(int productId, std::string productName, double priceAtPurchase, int quantity)
    : productId(productId), productName(productName), priceAtPurchase(priceAtPurchase), quantity(quantity) {}

int OrderItem::getProductId() const { return productId; }
std::string OrderItem::getProductName() const { return productName; }
double OrderItem::getPriceAtPurchase() const { return priceAtPurchase; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getSubtotal() const { return priceAtPurchase * quantity; }
