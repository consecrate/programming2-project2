#include "OrderItem.h"

#include <stdexcept>

OrderItem::OrderItem() : productId(0), productName(""), priceAtPurchase(0.0), quantity(0) {}

OrderItem::OrderItem(int productId, std::string productName, double priceAtPurchase, int quantity)
    : productId(productId), productName(productName), priceAtPurchase(priceAtPurchase), quantity(quantity) {
    if (priceAtPurchase < 0.0) {
        throw std::invalid_argument("priceAtPurchase must be non-negative");
    }
    if (quantity < 0) {
        throw std::invalid_argument("quantity must be non-negative");
    }
}

int OrderItem::getProductId() const { return productId; }
std::string OrderItem::getProductName() const { return productName; }
double OrderItem::getPriceAtPurchase() const { return priceAtPurchase; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getSubtotal() const { return priceAtPurchase * quantity; }
