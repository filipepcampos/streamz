#ifndef STREAMZ_STORE_H
#define STREAMZ_STORE_H
#include "Order.h"
#include <vector>
#include <queue>

class Store {
    Platform &platform;
    std::string streamer;
    unsigned int max_products_sold;
    unsigned int products_sold = 0;
    std::priority_queue<Order> orders;
    std::vector<Product> available_merchandise;
public:
    Store(const std::string &streamer, Platform &platform);
    bool addMerchandise(const Product &p);
    bool addMerchandise(const std::string &product_name, double price);
    bool removeMerchandise(const std::string &product_name);

    void showMerchandise() const;
    std::string getStreamer() const;
    Product getProductByPos(int pos) const;
    const std::vector<Product> & getProducts() const;
    bool placeOrder(const Order &o);
    bool removeOrder(const Order &o);
    void showOrders() const;
    void setProductsSold(unsigned int new_value);
    void changeMaxProductsSold(unsigned int new_size);
    unsigned getProductsSold() const;
    unsigned getMaxProductsSold() const;
    void resetProductsSold();
    bool full() const;
    void processOrders();
};


#endif //STREAMZ_STORE_H
