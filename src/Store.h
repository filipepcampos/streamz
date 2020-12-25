#ifndef STREAMZ_STORE_H
#define STREAMZ_STORE_H
#include "Order.h"
#include <vector>
#include <queue>

class Store {
    Platform &platform;
    std::string streamer;
    int max_orders = 5;
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
    void showOrders() const;
    void processOrder();
};


#endif //STREAMZ_STORE_H
