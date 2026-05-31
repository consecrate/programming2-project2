#include "Cart.h"
#include "Product.h"
#include "ProductManager.h"

#include <iomanip>
#include <iostream>

void Cart::addItem(int productId, int quantity) {
    if (quantity <= 0) return;
    for (auto& item : items) {
        if (item.getProductId() == productId) {
            item.setQuantity(item.getQuantity() + quantity);
            return;
        }
    }
    items.push_back(CartItem(productId, quantity));
}

bool Cart::removeItem(int productId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getProductId() == productId) {
            items.erase(it);
            return true;
        }
    }
    return false;
}

bool Cart::updateQuantity(int productId, int quantity) {
    if (quantity <= 0) return removeItem(productId);
    for (auto& item : items) {
        if (item.getProductId() == productId) {
            item.setQuantity(quantity);
            return true;
        }
    }
    return false;
}

bool Cart::isEmpty() const { return items.empty(); }

std::vector<int> Cart::getMissingProductIds(const ProductManager& productManager) const {
    std::vector<int> missingIds;
    for (const auto& item : items) {
        if (productManager.findProductById(item.getProductId()) == nullptr) {
            missingIds.push_back(item.getProductId());
        }
    }
    return missingIds;
}

bool Cart::hasMissingProducts(const ProductManager& productManager) const {
    return !getMissingProductIds(productManager).empty();
}

double Cart::calculateTotal(const ProductManager& productManager) const {
    auto missingIds = getMissingProductIds(productManager);
    if (!missingIds.empty()) {
        std::cout << "Cart contains unavailable product IDs: ";
        for (size_t i = 0; i < missingIds.size(); ++i) {
            std::cout << missingIds[i];
            if (i + 1 < missingIds.size()) std::cout << ", ";
        }
        std::cout << ". Total cannot be calculated.\n";
        return 0.0;
    }

    double total = 0.0;
    for (const auto& item : items) {
        const Product* product = productManager.findProductById(item.getProductId());
        total += product->getPrice() * item.getQuantity();
    }
    return total;
}

void Cart::displayCart(const ProductManager& productManager) const {
    if (items.empty()) {
        std::cout << "Your cart is empty.\n";
        return;
    }

    std::cout << "\n===== Shopping Cart =====\n";
    std::cout << std::left << std::setw(6) << "ID" << std::setw(28) << "Product"
              << std::right << std::setw(10) << "Price" << std::setw(10) << "Qty"
              << std::setw(12) << "Subtotal" << '\n';
    for (const auto& item : items) {
        const Product* product = productManager.findProductById(item.getProductId());
        if (product != nullptr) {
            double subtotal = product->getPrice() * item.getQuantity();
            std::cout << std::left << std::setw(6) << product->getId()
                      << std::setw(28) << product->getName()
                      << std::right << std::fixed << std::setprecision(2)
                      << std::setw(10) << product->getPrice()
                      << std::setw(10) << item.getQuantity()
                      << std::setw(12) << subtotal << '\n';
        } else {
            std::cout << std::left << std::setw(6) << item.getProductId()
                      << std::setw(28) << "[Unavailable product]"
                      << std::right << std::setw(10) << "-"
                      << std::setw(10) << item.getQuantity()
                      << std::setw(12) << "-" << '\n';
        }
    }
    std::cout << "Total: " << std::fixed << std::setprecision(2) << calculateTotal(productManager) << "\n";
}

void Cart::clear() { items.clear(); }
std::vector<CartItem> Cart::getItems() const { return items; }
