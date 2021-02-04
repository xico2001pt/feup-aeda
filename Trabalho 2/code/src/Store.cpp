#include "Store.h"
#include <algorithm>

Store::Store(const std::string &streamer, Platform &platform) : streamer(streamer), platform(platform) {
    max_products_sold = platform.getMaxProductsSold();
}

bool Store::addMerchandise(const Product &p) {
    auto it = std::find(available_merchandise.begin(), available_merchandise.end(), p);
    if(it == available_merchandise.end()){
        available_merchandise.push_back(p);
        return true;
    }
    return false;
}

bool Store::addMerchandise(const std::string &product_name, double price){
    return addMerchandise(Product(product_name,price));
}

bool Store::removeMerchandise(const std::string &product_name){
    auto it = std::find(available_merchandise.begin(), available_merchandise.end(), Product(product_name,0.0));
    if(it != available_merchandise.end()){
        available_merchandise.erase(it);
        return true;
    }
    return false;
}

void Store::showMerchandise() const{
    int i = 1;
    for(const auto &product : available_merchandise){
        std::cout << i++ << ".  \"" << product.getName() << "\" - " << product.getPrice() << "€\n";
    }
}

void Store::placeOrder(const Order &o) {
    orders.push(o);
    Viewer *v = o.getCustomer();
    v->addPendingOrder(o);
}

void Store::showOrders() const {
    std::priority_queue<Order> tmp_queue = orders;
    while(!tmp_queue.empty()){
        Order o = tmp_queue.top(); tmp_queue.pop();
        std::cout << o << std::endl;
    }
}

std::string Store::getStreamer() const {
    return streamer;
}

void Store::processOrders() {
    while(!orders.empty()){
        Order o = orders.top();
        if(products_sold+o.getSize() <= max_products_sold) {
            orders.pop();
            Viewer *v = o.getCustomer();
            v->completeOrder(o);
            products_sold += o.getSize();
        }
        else{
            break;
        }
    }
}

Product Store::getProductByPos(int pos) const {
    if(pos >= 0 && pos < available_merchandise.size()){
        return available_merchandise[pos];
    }
    throw ProductDoesntExist();
}

const std::vector<Product> &Store::getProducts() const {
    return available_merchandise;
}

bool Store::removeOrder(const Order &o) {
    std::priority_queue<Order> tmp_queue;
    bool found = false;
    while(!orders.empty()){
        Order o2 = orders.top(); orders.pop();
        if(!found && o == o2){
            found = true;
            continue;
        }
        tmp_queue.push(o);
    }
    orders = tmp_queue;
    return found;
}

void Store::changeMaxProductsSold(unsigned int new_max) {
    max_products_sold = new_max;
}

void Store::resetProductsSold() {
    products_sold = 0;
}

unsigned Store::getProductsSold() const {
    return products_sold;
}

unsigned Store::getMaxProductsSold() const {
    return max_products_sold;
}

void Store::setProductsSold(unsigned int new_value) {
    products_sold = new_value;
}
