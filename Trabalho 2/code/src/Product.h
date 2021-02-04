#ifndef STREAMZ_PRODUCT_H
#define STREAMZ_PRODUCT_H
#include <string>
#include <iostream>

class Product {
    std::string name; /*< Product name */
    double price; /*< Product price */
public:
    /**
     * Class constructor
     * @param name Product name
     * @param price Product value
     */
    Product(const std::string &name, double price);

    /*+
     * Get product name
     * @return Product's name
     */
    std::string getName() const;

    /**
     * Get product price
     * @return Product's price
     */
    double getPrice() const;

    bool operator==(const Product &p) const;
    friend std::ostream& operator <<(std::ostream& os, const Product &p);
};


#endif //STREAMZ_PRODUCT_H
