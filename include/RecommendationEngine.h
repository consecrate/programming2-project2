#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include "Product.h"
#include "ProductManager.h"

#include <vector>

class RecommendationEngine {
public:
    double calculateScore(const Product& product,
                          const std::vector<int>& viewedProductIds,
                          const std::vector<int>& purchasedProductIds,
                          const ProductManager& productManager) const;
    std::vector<Product> recommendTopN(const std::vector<Product>& products,
                                       const std::vector<int>& viewedProductIds,
                                       const std::vector<int>& purchasedProductIds,
                                       int n) const;
    bool hasPurchasedProduct(int productId, const std::vector<int>& purchasedProductIds) const;
    bool hasCategoryMatch(const Product& product,
                          const std::vector<int>& historyProductIds,
                          const std::vector<Product>& products) const;
};

#endif
