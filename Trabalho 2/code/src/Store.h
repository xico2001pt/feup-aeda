#ifndef STREAMZ_STORE_H
#define STREAMZ_STORE_H
#include "Order.h"
#include <vector>
#include <queue>

class Store {
    Platform &platform; /*< Associated Platform */
    std::string streamer; /*< Streamer nickname */
    unsigned int max_products_sold; /*< Max Products that can be sold limit */
    unsigned int products_sold = 0; /*< Current number of products sold*/
    std::priority_queue<Order> orders; /*< Orders queue */
    std::vector<Product> available_merchandise; /*< List of products available for sale */
public:
    /**
     * Class constructor
     * @param streamer Streamer nickname
     * @param platform Platform
     */
    Store(const std::string &streamer, Platform &platform);

    /**
     * Add product to available merchandise
     * @param p Product to be added
     * @return true if successful, false otherwise
     */
    bool addMerchandise(const Product &p);

    /**
     * Add product to available merchandise
     * @param product_name Product name
     * @param price Product price
     * @return true if successful, false otherwise
     */
    bool addMerchandise(const std::string &product_name, double price);

    /**
     * Remove product from available merchandise
     * @param product_name Product name
     * @return true if successful, false otherwise
     */
    bool removeMerchandise(const std::string &product_name);

    /**
     * Show available merchandise
     */
    void showMerchandise() const;

    /**
     * Get streamer's nickname
     * @return String with streamer's nickanem
     */
    std::string getStreamer() const;

    /**
     * Get product at index 'pos' of available merchandise
     * @param pos Index
     * @return Product chosen
     */
    Product getProductByPos(int pos) const;

    /**
     * Get available products for sale
     * @return Vector with all available products
     */
    const std::vector<Product> & getProducts() const;

    /**
     * Place an order
     * @param o Order to be placed
     */
    void placeOrder(const Order &o);

    /**
     * Remove a order
     * @param o Order to be removed
     * @return true if successful, false otherwise
     */
    bool removeOrder(const Order &o);

    /**
     * Show all orders
     */
    void showOrders() const;

    /**
     * Set products_sold value
     * @param new_value New products_sold value
     */
    void setProductsSold(unsigned int new_value);

    /**
     * Change limit of products that can be sold
     * @param new_size New value
     */
    void changeMaxProductsSold(unsigned int new_size);

    /**
     * Get number of total products sold by the store
     * @return Number of products sold
     */
    unsigned getProductsSold() const;

    /**
     * Get maximum number of products sold by the store
     * @return Number of products sold
     */
    unsigned getMaxProductsSold() const;

    /**
     * Set number of products sold to zero
     */
    void resetProductsSold();

    /**
     * Process as many orders as possible within the maximum products restriction
     */
    void processOrders();
};


#endif //STREAMZ_STORE_H
