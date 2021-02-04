#ifndef STREAMZ_ORDER_H
#define STREAMZ_ORDER_H
#include <vector>
#include <iostream>
#include "Product.h"
#include "Viewer.h"

class Order {
    std::vector<Product> products; /* Products */
    Viewer *customer; /* Pointer to customer */
    std::string streamer; /* Store streamer's nickname */
    unsigned disp = 0; /* 'Disponibilidade de compra'*/
    bool completed = false;
public:
    /**
     * Class constructor
     * @param customer Pointer to viewer
     * @param disp Purchase availability
     * @param streamer Streamer's nickname
     */
    Order(Viewer *customer, unsigned disp, const std::string &streamer);

    /**
     * Add a product to the order
     * @param product Product
     */
    void addProduct(const Product &product);

    /**
     * Remove a product from the order
     * @param product Product
     */
    void removeProduct(const Product &product);

    /**
     * Return sum of all product's prices
     * @return Total Order price
     */
    double getTotalPrice() const;

    /**
     * Return order size
     * @return Number of products
     */
    int getSize() const;

    /**
     * Return purchase availability
     * @return number from 1 to 5
     */
    int getDisp() const;

    /**
     * Set purchase availability
     * @param disp Value between 1 and 5
     */
    void setDisp(unsigned disp);

    /**
     * Set order as complete
     */
    void completeOrder();

    /**
     * Get pointer to viewer that made the order
     * @return pointer
     */
    Viewer * getCustomer() const;

    /**
     * Get customer's nickname
     * @return Customer nickname
     */
    std::string getCustomerNickname() const;

    /**
     * Get streamer's nickname
     * @return Streamer nickname
     */
    std::string getStreamer() const;
    bool operator==(const Order &o) const;
    bool operator<(const Order &o) const;
    friend std::ostream& operator <<(std::ostream& os, const Order &o);
};


#endif //STREAMZ_ORDER_H
