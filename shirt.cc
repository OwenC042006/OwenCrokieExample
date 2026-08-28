#include "shirt.h"

void Shirt::input() {
    cin >> size >> color >> price;
}

void Shirt::output() {
    cout << "Shirt: " << size << " " << color << " $" << price << endl;
}

double Shirt::getCost() {
    return price;
}

string Shirt::getType() const {
    return "Shirt";
}

void Shirt::save(ostream &out) const {
    out << size << " " << color << " " << price << "\n";
}

void Shirt::load(istream &in) {
    in >> size >> color >> price;
}

Product *Shirt::clone() const {
    return new Shirt(*this);
}