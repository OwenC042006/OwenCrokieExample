#include "product.h"

void Phone::input() {
    cin >> brand >> storage >> price;
}

void Phone::output() {
    cout << "Phone: " << brand << " " << storage << "GB $" << price << endl;
}

double Phone::getCost() {
    return price;
}

string Phone::getType() const {
    return "Phone";
}

void Phone::save(ostream &out) const {
    out << brand << " " << storage << " " << price << "\n";
}

void Phone::load(istream &in) {
    in >> brand >> storage >> price;
}

Product *Phone::clone() const {
    return new Phone(*this);
}

void Food::input() {
    cin >> name >> calories >> price;
}

void Food::output() {
    cout << "Food: " << name << " " << calories << "cal $" << price << endl;
}

double Food::getCost() {
    return price;
}

string Food::getType() const {
    return "Food";
}

void Food::save(ostream &out) const {
    out << name << " " << calories << " " << price << "\n";
}

void Food::load(istream &in) {
    in >> name >> calories >> price;
}

Product *Food::clone() const {
    return new Food(*this);
}