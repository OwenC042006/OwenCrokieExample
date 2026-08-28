#include "book.h"

void Book::input() {
    cin >> title >> pages >> price;
}

void Book::output() {
    cout << "Book: " << title << " " << pages << " pages $" << price << endl;
}

double Book::getCost() {
    return price;
}

string Book::getType() const {
    return "Book";
}

void Book::save(ostream &out) const {
    out << title << " " << pages << " " << price << "\n";
}

void Book::load(istream &in) {
    in >> title >> pages >> price;
}

Product *Book::clone() const {
    return new Book(*this);
}