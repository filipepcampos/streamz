//
// Created by filipe on 20/12/20.
//

#include "Order.h"

// TODO: Check if i if between 1 and 5
Order::Order(Viewer *customer, int disp, const std::string &streamer) : customer(customer), disp(disp), streamer(streamer){
}

void Order::addProduct(const Product &product) {
    products.push_back(product);
}

double Order::getTotalPrice() const {
    double total = 0.0;
    for(const auto &p : products){
        total += p.getPrice();
    }
    return total;
}

int Order::getSize() const {
    return products.size();
}

int Order::getDisp() const {
    return disp;
}

bool Order::operator<(const Order &o) const {
    if(getSize() == o.getSize()){
        return getDisp() < o.getDisp();
    }
    return getSize() > o.getSize();
}

std::ostream &operator<<(std::ostream &os, const Order &o) {
    os << o.customer->getNickname() << " " << o.getDisp() << std::endl;
    for(const auto &prod : o.products){
        os << prod << std::endl;
    }
    return os;
}
