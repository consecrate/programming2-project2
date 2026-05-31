#include "RecommendationEngine.h"

#include <algorithm>
#include <iostream>
#include <utility>

bool RecommendationEngine::hasPurchasedProduct(int productId, const std::vector<int>& purchasedProductIds) const {
    return std::find(purchasedProductIds.begin(), purchasedProductIds.end(), productId) != purchasedProductIds.end();
}

bool RecommendationEngine::hasCategoryMatch(const Product& product,
                                            const std::vector<int>& historyProductIds,
                                            const std::vector<Product>& products) const {
    for (int historyId : historyProductIds) {
        for (const auto& historyProduct : products) {
            if (historyProduct.getId() == historyId && historyProduct.getCategory() == product.getCategory()) {
                return true;
            }
        }
    }
    return false;
}

double RecommendationEngine::calculateScore(const Product& product,
                                            const std::vector<int>& viewedProductIds,
                                            const std::vector<int>& purchasedProductIds,
                                            const ProductManager& productManager) const {
    double categoryBonus = 0.0;
    const std::vector<Product>& products = productManager.getProducts();

    if (hasCategoryMatch(product, purchasedProductIds, products)) {
        categoryBonus = 1.5;
    } else if (hasCategoryMatch(product, viewedProductIds, products)) {
        categoryBonus = 0.8;
    }

    return product.getViewCount() * 0.2 + product.getPurchaseCount() * 0.8 + categoryBonus;
}

std::vector<Product> RecommendationEngine::recommendTopN(const std::vector<Product>& products,
                                                         const std::vector<int>& viewedProductIds,
                                                         const std::vector<int>& purchasedProductIds,
                                                         int n) const {
    std::vector<std::pair<Product, double>> scoredProducts;

    for (const auto& product : products) {
        if (hasPurchasedProduct(product.getId(), purchasedProductIds)) {
            continue;
        }

        double categoryBonus = 0.0;
        if (hasCategoryMatch(product, purchasedProductIds, products)) {
            categoryBonus = 1.5;
        } else if (hasCategoryMatch(product, viewedProductIds, products)) {
            categoryBonus = 0.8;
        }

        double score = product.getViewCount() * 0.2 + product.getPurchaseCount() * 0.8 + categoryBonus;
        scoredProducts.push_back({product, score});
    }

    std::sort(scoredProducts.begin(), scoredProducts.end(),
              [](const auto& a, const auto& b) {
                  if (a.second == b.second) return a.first.getId() < b.first.getId();
                  return a.second > b.second;
              });

    std::vector<Product> result;
    int limit = std::min(n, static_cast<int>(scoredProducts.size()));
    for (int i = 0; i < limit; ++i) {
        result.push_back(scoredProducts[i].first);
    }
    return result;
}