#ifndef CART_ITEM_H
#define CART_ITEM_H

class CartItem {
private:
    int productId;
    int quantity;

public:
    CartItem();
    CartItem(int productId, int quantity);

    int getProductId() const;
    int getQuantity() const;
    void setQuantity(int quantity);
};

#endif
