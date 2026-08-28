#include "food.h"

void Food::input() {
    cin >> name >> calories >> price;
}

void Food::output() {
    cout << name << " " << calories << " " << price << endl;
}

double Food::getCost() {
    return price;
}