#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>

class Interaction {
private:
    int customerId;
    int productId;
    std::string type;
    int count;

public:
    Interaction();
    Interaction(int customerId, int productId, std::string type, int count);

    int getCustomerId() const;
    int getProductId() const;
    std::string getType() const;
    int getCount() const;
    void incrementCount();
};

#endif
