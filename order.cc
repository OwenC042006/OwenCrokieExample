#include "order.h"
#include "book.h"
#include "shirt.h"

Order::Order() : customerName(""), items() {}

Order::Order(const string& name) : customerName(name), items() {}

Order::Order(const Order& other) : customerName(other.customerName), items() {
    for (Product* p : other.items) {
        if (p)
            items.push_back(p->clone());
    }
}

Order& Order::operator=(const Order& other) {
    if (this == &other) return *this;
    clearItems();
    customerName = other.customerName;
    for (Product* p : other.items) {
        if (p)
            items.push_back(p->clone());
    }
    return *this;
}

Order::~Order() {
    clearItems();
}

void Order::clearItems() {
    for (Product* p : items) {
        delete p;
    }
    items.clear();
}

void Order::setCustomerName(const string& name) {
    customerName = name;
}

string Order::getCustomerName() const {
    return customerName;
}

void Order::addItem(Product* item) {
    if (item)
        items.push_back(item);
}

bool Order::hasItems() const {
    return !items.empty();
}

double Order::getTotalCost() const {
    double total = 0.0;
    for (Product* p : items) {
        if (p)
            total += p->getCost();
    }
    return total;
}

void Order::output() const {
    cout << "Order for: " << customerName << "\n";
    cout << "Total items: " << items.size() << "  Total cost: $" << getTotalCost() << "\n";
    cout << "Items:" << endl;
    for (Product* p : items) {
        if (p)
            p->output();
    }
    cout << "------------------------------" << endl;
}

void Order::save(ostream& out) const {
    out << customerName << "\n";
    out << items.size() << "\n";
    for (Product* p : items) {
        out << p->getType() << "\n";
        p->save(out);
    }
}

void Order::load(istream& in) {
    clearItems();
    string name;
    if (!getline(in, name)) {
        customerName = "";
        return;
    }
    customerName = name;

    size_t itemCount;
    if (!(in >> itemCount)) {
        return;
    }
    string dummy;
    getline(in, dummy); // consume end-of-line after itemCount

    for (size_t i = 0; i < itemCount; i++) {
        string type;
        if (!getline(in, type)) break;
        Product* p = nullptr;
        if (type == "Phone") {
            p = new Phone();
        } else if (type == "Food") {
            p = new Food();
        } else if (type == "Book") {
            p = new Book();
        } else if (type == "Shirt") {
            p = new Shirt();
        } else {
            continue;
        }
        if (p) {
            p->load(in);
            items.push_back(p);
        }
    }
}
