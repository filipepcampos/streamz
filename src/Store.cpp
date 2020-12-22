#include "Store.h"
#include <algorithm>

Store::Store(const std::string &streamer, Platform &platform) : streamer(streamer), platform(platform) {
}

bool Store::addMerchandise(const Product &p) {
    auto it = std::find(available_merchandise.begin(), available_merchandise.end(), p);
    if(it == available_merchandise.end()){
        available_merchandise.push_back(p);
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

bool Store::placeOrder(const Order &o) {
    if(orders.size() < max_orders){
        orders.push(o);
        return true;
    }
    return false;
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

void Store::processOrder() {
    if(!orders.empty()){
        Order o = orders.top(); orders.pop();
        User * u = platform.getUser(o.getCustomerNickname());
        Viewer *v = dynamic_cast<Viewer *> (u);
        if(v != nullptr){
            v->completeOrder(o);
        }
    }
}

Product Store::getProductByPos(int pos) const {
    if(pos >= 0 && pos < available_merchandise.size()){
        return available_merchandise[pos];
    }
    return Product("",0.0); // TODO: Throw exception
}
