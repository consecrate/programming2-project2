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
    std::vector<int> getMissingProductIds(const ProductManager& productManager) const;
    bool hasMissingProducts(const ProductManager& productManager) const;
    double calculateTotal(const ProductManager& productManager) const;
    void displayCart(const ProductManager& productManager) const;
    void clear();
    std::vector<CartItem> getItems() const;
};

#endif
