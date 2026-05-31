#include "Customer.h"
#include "FileManager.h"
#include "OrderManager.h"
#include "Product.h"
#include "ProductManager.h"
#include "RecommendationEngine.h"
#include "Utils.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace {
    void recordInteraction(std::vector<Interaction>& interactions,
                           int customerId,
                           int productId,
                           const std::string& type,
                           int countToAdd) {
        if (countToAdd <= 0) return;
        for (auto& interaction : interactions) {
            if (interaction.getCustomerId() == customerId &&
                interaction.getProductId() == productId &&
                interaction.getType() == type) {
                for (int i = 0; i < countToAdd; ++i) {
                    interaction.incrementCount();
                }
                return;
            }
        }
        interactions.push_back(Interaction(customerId, productId, type, countToAdd));
    }
}

Customer::Customer() : User(), cart(), viewedProductIds(), purchasedProductIds() {}

Customer::Customer(int userId, std::string name, std::string email, std::string password)
    : User(userId, name, email, password, "customer"), cart(), viewedProductIds(), purchasedProductIds() {}

void Customer::showMenu(ProductManager& productManager,
                        OrderManager& orderManager,
                        RecommendationEngine& recommendationEngine,
                        FileManager& fileManager) {
    static std::vector<Interaction> temporaryInteractions;
    showMenu(productManager, orderManager, recommendationEngine, fileManager, temporaryInteractions);
}

void Customer::showMenu(ProductManager& productManager,
                        OrderManager& orderManager,
                        RecommendationEngine& recommendationEngine,
                        FileManager& fileManager,
                        std::vector<Interaction>& interactions) {
    (void)fileManager;
    int choice;
    do {
        std::cout << "\n===== Customer Menu =====\n"
                  << "1. Browse all products\n"
                  << "2. Search product by ID\n"
                  << "3. Filter products by category\n"
                  << "4. Add product to cart\n"
                  << "5. Remove product from cart\n"
                  << "6. Update cart quantity\n"
                  << "7. View cart\n"
                  << "8. Checkout\n"
                  << "9. View order history\n"
                  << "10. View recommendations\n"
                  << "0. Logout\n";
        choice = getValidatedInt("Choose an option: ");

        if (choice == 1) {
            browseProducts(productManager);
        } else if (choice == 2) {
            int id = getValidatedInt("Enter product ID: ");
            viewProductDetails(productManager, id, interactions);
        } else if (choice == 3) {
            std::string category;
            std::cout << "Enter category: ";
            std::getline(std::cin, category);
            productManager.displayProductsByCategory(category);
        } else if (choice == 4) {
            int id = getValidatedInt("Product ID: ");
            int quantity = getValidatedInt("Quantity: ");
            addToCart(productManager, id, quantity);
        } else if (choice == 5) {
            int id = getValidatedInt("Product ID to remove: ");
            removeFromCart(id);
        } else if (choice == 6) {
            int id = getValidatedInt("Product ID to update: ");
            int quantity = getValidatedInt("New quantity: ");
            updateCartQuantity(id, quantity);
        } else if (choice == 7) {
            cart.displayCart(productManager);
        } else if (choice == 8) {
            checkout(productManager, orderManager, interactions);
        } else if (choice == 9) {
            viewOrderHistory(orderManager);
        } else if (choice == 10) {
            viewRecommendations(productManager, recommendationEngine);
        } else if (choice == 0) {
            std::cout << "Logging out...\n";
        } else {
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);
}

void Customer::browseProducts(ProductManager& productManager) {
    productManager.displayAllProducts();
}

void Customer::viewProductDetails(ProductManager& productManager, int productId) {
    Product* product = productManager.findProductById(productId);
    if (product == nullptr) {
        std::cout << "Product not found.\n";
        return;
    }
    product->incrementViewCount();
    addViewedProductId(productId);
    product->displayDetails();
}

void Customer::viewProductDetails(ProductManager& productManager, int productId, std::vector<Interaction>& interactions) {
    Product* product = productManager.findProductById(productId);
    if (product == nullptr) {
        std::cout << "Product not found.\n";
        return;
    }
    product->incrementViewCount();
    addViewedProductId(productId);
    recordInteraction(interactions, getUserId(), productId, "view", 1);
    product->displayDetails();
}

void Customer::addToCart(ProductManager& productManager, int productId, int quantity) {
    Product* product = productManager.findProductById(productId);
    if (product == nullptr) {
        std::cout << "Product not found.\n";
        return;
    }
    if (quantity <= 0) {
        std::cout << "Quantity must be positive.\n";
        return;
    }
    if (quantity > product->getStock()) {
        std::cout << "Not enough stock. Available stock: " << product->getStock() << "\n";
        return;
    }
    cart.addItem(productId, quantity);
    std::cout << "Added to cart.\n";
}

void Customer::removeFromCart(int productId) {
    if (cart.removeItem(productId)) std::cout << "Item removed from cart.\n";
    else std::cout << "Item was not found in cart.\n";
}

void Customer::updateCartQuantity(int productId, int quantity) {
    if (cart.updateQuantity(productId, quantity)) std::cout << "Cart updated.\n";
    else std::cout << "Item was not found in cart.\n";
}

void Customer::checkout(ProductManager& productManager, OrderManager& orderManager) {
    static std::vector<Interaction> temporaryInteractions;
    checkout(productManager, orderManager, temporaryInteractions);
}

void Customer::checkout(ProductManager& productManager, OrderManager& orderManager, std::vector<Interaction>& interactions) {
    if (cart.isEmpty()) {
        std::cout << "Cart is empty.\n";
        return;
    }

    std::vector<CartItem> cartItemsBeforeCheckout = cart.getItems();
    Order order = orderManager.createOrder(getUserId(), cart, productManager);
    if (order.getOrderId() > 0) {
        for (const auto& item : cartItemsBeforeCheckout) {
            addPurchasedProductId(item.getProductId());
            recordInteraction(interactions, getUserId(), item.getProductId(), "purchase", item.getQuantity());
        }
        std::cout << "Checkout successful.\n";
        order.displayOrder();
    }
}

void Customer::viewOrderHistory(OrderManager& orderManager) const {
    orderManager.displayOrdersByCustomerId(getUserId());
}

void Customer::viewRecommendations(ProductManager& productManager, RecommendationEngine& recommendationEngine) {
    int n = getValidatedInt("How many recommendations do you want? ");
    auto recommendations = recommendationEngine.recommendTopN(productManager.getProducts(), viewedProductIds, purchasedProductIds, n);

    std::cout << "\n===== Top Recommendations =====\n";
    if (recommendations.empty()) {
        std::cout << "No recommendations available yet.\n";
        return;
    }

    std::cout << std::left << std::setw(6) << "Rank" << std::setw(5) << "ID"
              << std::setw(28) << "Name" << std::setw(18) << "Category"
              << std::right << std::setw(10) << "Score" << '\n';
    for (size_t i = 0; i < recommendations.size(); ++i) {
        double score = recommendationEngine.calculateScore(recommendations[i], viewedProductIds,
                                                           purchasedProductIds, productManager);
        std::cout << std::left << std::setw(6) << (i + 1)
                  << std::setw(5) << recommendations[i].getId()
                  << std::setw(28) << recommendations[i].getName()
                  << std::setw(18) << recommendations[i].getCategory()
                  << std::right << std::fixed << std::setprecision(2)
                  << std::setw(10) << score << '\n';
    }
}

std::vector<int> Customer::getViewedProductIds() const { return viewedProductIds; }
std::vector<int> Customer::getPurchasedProductIds() const { return purchasedProductIds; }

void Customer::addViewedProductId(int productId) {
    if (std::find(viewedProductIds.begin(), viewedProductIds.end(), productId) == viewedProductIds.end()) {
        viewedProductIds.push_back(productId);
    }
}

void Customer::addPurchasedProductId(int productId) {
    if (std::find(purchasedProductIds.begin(), purchasedProductIds.end(), productId) == purchasedProductIds.end()) {
        purchasedProductIds.push_back(productId);
    }
}