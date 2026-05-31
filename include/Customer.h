#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Cart.h"
#include "Interaction.h"
#include "User.h"

#include <vector>

class FileManager;
class OrderManager;
class ProductManager;
class RecommendationEngine;

class Customer : public User {
private:
    Cart cart;
    std::vector<int> viewedProductIds;
    std::vector<int> purchasedProductIds;

public:
    Customer();
    Customer(int userId, std::string name, std::string email, std::string password);

    void showMenu(ProductManager& productManager,
                  OrderManager& orderManager,
                  RecommendationEngine& recommendationEngine,
                  FileManager& fileManager);
    void showMenu(ProductManager& productManager,
                  OrderManager& orderManager,
                  RecommendationEngine& recommendationEngine,
                  FileManager& fileManager,
                  std::vector<Interaction>& interactions);
    void browseProducts(ProductManager& productManager);
    void viewProductDetails(ProductManager& productManager, int productId);
    void viewProductDetails(ProductManager& productManager, int productId, std::vector<Interaction>& interactions);
    void addToCart(ProductManager& productManager, int productId, int quantity);
    void removeFromCart(int productId);
    void updateCartQuantity(int productId, int quantity);
    void checkout(ProductManager& productManager, OrderManager& orderManager);
    void checkout(ProductManager& productManager, OrderManager& orderManager, std::vector<Interaction>& interactions);
    void viewOrderHistory(OrderManager& orderManager) const;
    void viewRecommendations(ProductManager& productManager, RecommendationEngine& recommendationEngine);

    std::vector<int> getViewedProductIds() const;
    std::vector<int> getPurchasedProductIds() const;
    void addViewedProductId(int productId);
    void addPurchasedProductId(int productId);
};

#endif
