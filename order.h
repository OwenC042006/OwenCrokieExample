#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <list>
#include <string>
#include "product.h"

using namespace std;

class Order {
private:
    string customerName;
    list<Product*> items;

    void clearItems();
public:
    Order();
    Order(const string& name);
    Order(const Order& other);
    Order& operator=(const Order& other);
    ~Order();

    void setCustomerName(const string& name);
    string getCustomerName() const;

    void addItem(Product* item);
    bool hasItems() const;
    double getTotalCost() const;

    void output() const;

    void save(ostream &out) const;
    void load(istream &in);
};

#endif