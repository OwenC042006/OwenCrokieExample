#include "product.h"

class Book : public Product {
private:
    string title;
    int pages;
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