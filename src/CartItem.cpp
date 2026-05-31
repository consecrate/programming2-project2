#include "CartItem.h"

CartItem::CartItem() : productId(0), quantity(0) {}
CartItem::CartItem(int productId, int quantity) : productId(productId), quantity(quantity) {}

int CartItem::getProductId() const { return productId; }
int CartItem::getQuantity() const { return quantity; }
void CartItem::setQuantity(int quantity) { if (quantity >= 0) this->quantity = quantity; }
