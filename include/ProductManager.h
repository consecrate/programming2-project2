#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "Product.h"

#include <string>
#include <vector>

class ProductManager {
private:
    std::vector<Product> products;

public:
    std::vector<Product>& getProducts();
    const std::vector<Product>& getProducts() const;

    Product* findProductById(int id);
    const Product* findProductById(int id) const;
    bool productExists(int id) const;
    void addProduct(const Product& product);
    bool editProduct(int id);
    bool deleteProduct(int id);
    void displayAllProducts() const;
    void displayProductsByCategory(std::string category) const;
};

#endif
