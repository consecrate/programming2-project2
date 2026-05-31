#include "Interaction.h"

#include <stdexcept>

Interaction::Interaction() : customerId(0), productId(0), type(""), count(0) {}

Interaction::Interaction(int customerId, int productId, std::string type, int count)
    : customerId(customerId),
      productId(productId),
      type(type),
      count(count) {
    if (count < 0) {
        throw std::invalid_argument("count must be non-negative");
    }
}

int Interaction::getCustomerId() const { return customerId; }
int Interaction::getProductId() const { return productId; }
std::string Interaction::getType() const { return type; }
int Interaction::getCount() const { return count; }

void Interaction::incrementCount() { ++count; }
