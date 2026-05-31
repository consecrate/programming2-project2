#ifndef STATISTICS_MANAGER_H
#define STATISTICS_MANAGER_H

#include "Interaction.h"
#include "Product.h"

#include <utility>
#include <vector>

class StatisticsManager {
public:
    std::vector<Product> getMostViewedProducts(const std::vector<Product>& products, int limit) const;
    std::vector<Product> getBestSellingProducts(const std::vector<Product>& products, int limit) const;
    std::vector<std::pair<int, int>> getActiveUsers(const std::vector<Interaction>& interactions, int limit) const;

    void displayMostViewedProducts(const std::vector<Product>& products, int limit) const;
    void displayBestSellingProducts(const std::vector<Product>& products, int limit) const;
    void displayActiveUsers(const std::vector<Interaction>& interactions, int limit) const;
};

#endif
