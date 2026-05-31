#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int stock;
    int viewCount;
    int purchaseCount;

public:
    Product();
    Product(int id, std::string name, std::string category, double price, int stock);
    Product(int id, std::string name, std::string category, double price, int stock,
            int viewCount, int purchaseCount);

    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getStock() const;
    int getViewCount() const;
    int getPurchaseCount() const;

    void setName(std::string name);
    void setCategory(std::string category);
    void setPrice(double price);
    void setStock(int stock);
    void setViewCount(int viewCount);
    void setPurchaseCount(int purchaseCount);

    void incrementViewCount();
    void incrementPurchaseCount(int quantity);
    void reduceStock(int quantity);
    void displaySummary() const;
    void displayDetails() const;
};

#endif
