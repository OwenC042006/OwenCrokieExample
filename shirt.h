#include "product.h"

class Shirt : public Product {
private:
    string size;
    string color;
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