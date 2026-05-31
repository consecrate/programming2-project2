#ifndef CART_H
#define CART_H

#include "CartItem.h"

#include <vector>

class ProductManager;

class Cart {
private:
    std::vector<CartItem> items;

public:
    void addItem(int productId, int quantity);
    bool removeItem(int productId);
    bool updateQuantity(int productId, int quantity);
    bool isEmpty() const;
    double calculateTotal(const ProductManager& productManager) const;
    void displayCart(const ProductManager& productManager) const;
    void clear();
    std::vector<CartItem> getItems() const;
};

#endif
