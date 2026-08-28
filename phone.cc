#include "product.h"

void Phone::input() {
    cin >> brand >> storage >> price;
}

void Phone::output() {
    cout << brand << " " << storage << " " << price << endl;
}

double Phone::getCost() {
    return price;
}
