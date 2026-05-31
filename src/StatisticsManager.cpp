#include "StatisticsManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

std::vector<Product> StatisticsManager::getMostViewedProducts(const std::vector<Product>& products, int limit) const {
    std::vector<Product> sortedProducts = products;
    std::sort(sortedProducts.begin(), sortedProducts.end(),
              [](const Product& a, const Product& b) {
                  if (a.getViewCount() == b.getViewCount()) return a.getId() < b.getId();
                  return a.getViewCount() > b.getViewCount();
              });
    if (limit > 0 && limit < static_cast<int>(sortedProducts.size())) {
        sortedProducts.resize(limit);
    }
    return sortedProducts;
}

std::vector<Product> StatisticsManager::getBestSellingProducts(const std::vector<Product>& products, int limit) const {
    std::vector<Product> sortedProducts = products;
    std::sort(sortedProducts.begin(), sortedProducts.end(),
              [](const Product& a, const Product& b) {
                  if (a.getPurchaseCount() == b.getPurchaseCount()) return a.getId() < b.getId();
                  return a.getPurchaseCount() > b.getPurchaseCount();
              });
    if (limit > 0 && limit < static_cast<int>(sortedProducts.size())) {
        sortedProducts.resize(limit);
    }
    return sortedProducts;
}

std::vector<std::pair<int, int>> StatisticsManager::getActiveUsers(const std::vector<Interaction>& interactions, int limit) const {
    std::map<int, int> activityByUser;
    for (const auto& interaction : interactions) {
        activityByUser[interaction.getCustomerId()] += interaction.getCount();
    }

    std::vector<std::pair<int, int>> activeUsers(activityByUser.begin(), activityByUser.end());
    std::sort(activeUsers.begin(), activeUsers.end(),
              [](const auto& a, const auto& b) {
                  if (a.second == b.second) return a.first < b.first;
                  return a.second > b.second;
              });

    if (limit > 0 && limit < static_cast<int>(activeUsers.size())) {
        activeUsers.resize(limit);
    }
    return activeUsers;
}

void StatisticsManager::displayMostViewedProducts(const std::vector<Product>& products, int limit) const {
    auto mostViewed = getMostViewedProducts(products, limit);
    std::cout << "\nMost Viewed Products\n" << std::string(60, '-') << '\n';
    if (mostViewed.empty()) {
        std::cout << "No products available.\n";
        return;
    }
    std::cout << std::left << std::setw(6) << "Rank" << std::setw(5) << "ID"
              << std::setw(28) << "Name" << std::right << std::setw(10) << "Views" << '\n';
    for (size_t i = 0; i < mostViewed.size(); ++i) {
        std::cout << std::left << std::setw(6) << (i + 1)
                  << std::setw(5) << mostViewed[i].getId()
                  << std::setw(28) << mostViewed[i].getName()
                  << std::right << std::setw(10) << mostViewed[i].getViewCount() << '\n';
    }
}

void StatisticsManager::displayBestSellingProducts(const std::vector<Product>& products, int limit) const {
    auto bestSelling = getBestSellingProducts(products, limit);
    std::cout << "\nBest-Selling Products\n" << std::string(60, '-') << '\n';
    if (bestSelling.empty()) {
        std::cout << "No products available.\n";
        return;
    }
    std::cout << std::left << std::setw(6) << "Rank" << std::setw(5) << "ID"
              << std::setw(28) << "Name" << std::right << std::setw(12) << "Purchases" << '\n';
    for (size_t i = 0; i < bestSelling.size(); ++i) {
        std::cout << std::left << std::setw(6) << (i + 1)
                  << std::setw(5) << bestSelling[i].getId()
                  << std::setw(28) << bestSelling[i].getName()
                  << std::right << std::setw(12) << bestSelling[i].getPurchaseCount() << '\n';
    }
}

void StatisticsManager::displayActiveUsers(const std::vector<Interaction>& interactions, int limit) const {
    auto activeUsers = getActiveUsers(interactions, limit);
    std::cout << "\nActive Users\n" << std::string(40, '-') << '\n';
    if (activeUsers.empty()) {
        std::cout << "No user interactions recorded yet.\n";
        return;
    }
    std::cout << std::left << std::setw(6) << "Rank" << std::setw(12) << "User ID"
              << std::right << std::setw(16) << "Activity Score" << '\n';
    for (size_t i = 0; i < activeUsers.size(); ++i) {
        std::cout << std::left << std::setw(6) << (i + 1)
                  << std::setw(12) << activeUsers[i].first
                  << std::right << std::setw(16) << activeUsers[i].second << '\n';
    }
}