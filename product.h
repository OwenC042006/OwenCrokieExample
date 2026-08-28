#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

class Product {
public:
    virtual void input() = 0;
    virtual void output() = 0;
    virtual double getCost() = 0;
    virtual string getType() const = 0;
    virtual void save(ostream &out) const = 0;
    virtual void load(istream &in) = 0;
    virtual Product *clone() const = 0;
    virtual ~Product() {};
};

class Phone : public Product {
private:
    string brand;
    int storage;
    double price;
public:
    void input();
    void output();
    double getCost();
    string getType() const;
    void save(ostream &out) const;
    void load(istream &in);
    Product *clone() const;
};

class Food : public Product {
private:
    string name;
    int calories;
    double price;
public:
    void input();
    void output();
    double getCost();
    string getType() const;
    void save(ostream &out) const;
    void load(istream &in);
    Product *clone() const;
};

#endif