#ifndef STREAMZ_ORDER_H
#define STREAMZ_ORDER_H
#include <vector>
#include <iostream>
#include "Product.h"
#include "Viewer.h"

class Order {
    std::vector<Product> products;
    Viewer *customer;
    std::string streamer;
    int disp;
public:
    Order(Viewer *customer, int disp, const std::string &streamer);
    void addProduct(const Product &product);
    double getTotalPrice() const;
    int getSize() const;
    int getDisp() const;
    std::string getCustomerNickname() const;
    bool operator==(const Order &o) const;
    bool operator<(const Order &o) const;
    friend std::ostream& operator <<(std::ostream& os, const Order &o);
};


#endif //STREAMZ_ORDER_H
