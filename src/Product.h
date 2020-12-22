#ifndef STREAMZ_PRODUCT_H
#define STREAMZ_PRODUCT_H
#include <string>
#include <iostream>

class Product {
    std::string name;
    double price;
public:
    Product(const std::string &name, double price);
    std::string getName() const;
    double getPrice() const;
    bool operator==(const Product &p) const;
    friend std::ostream& operator <<(std::ostream& os, const Product &p);
};


#endif //STREAMZ_PRODUCT_H
