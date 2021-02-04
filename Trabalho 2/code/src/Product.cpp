#include "Product.h"

Product::Product(const std::string &name, double price) : name(name), price(price) {
}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

bool Product::operator==(const Product &p) const {
    return getName() == p.getName();
}

std::ostream &operator<<(std::ostream &os, const Product &p) {
    os << p.getName() << " " << p.getPrice() << "€" << std::endl;
    return os;
}
