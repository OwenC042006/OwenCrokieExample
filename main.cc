#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "book.h"
#include "food.h"
#include "order.h"
#include "phone.h"
#include "shirt.h"

using namespace std;

void saveOrders(const list<Order>& orders, const string& filename) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: unable to write backup file " << filename << endl;
        return;
    }
    out << orders.size() << "\n";
    for (const Order& o : orders) {
        o.save(out);
    }
}

void loadOrders(list<Order>& orders, const string& filename) {
    ifstream in(filename);
    if (!in) return;

    size_t orderCount;
    if (!(in >> orderCount)) return;
    string dummy;
    getline(in, dummy); // consume rest of first line

    for (size_t i = 0; i < orderCount; i++) {
        Order o;
        o.load(in);
        if (!o.getCustomerName().empty() || o.hasItems()) {
            orders.push_back(o);
        }
    }
}

Product* createProductByMenu() {
    cout << "Choose a product type to add:\n";
    cout << "1) Phone\n";
    cout << "2) Food\n";
    cout << "3) Book\n";
    cout << "4) Shirt\n";
    cout << "Enter choice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return nullptr;
    }
    cin.ignore(1000, '\n');
    Product* p = nullptr;
    if (choice == 1) p = new Phone();
    else if (choice == 2) p = new Food();
    else if (choice == 3) p = new Book();
    else if (choice == 4) p = new Shirt();
    else {
        cout << "Invalid choice.\n";
        return nullptr;
    }

    cout << "Enter attributes in one line as required for the product (space-separated):\n";
    if (choice == 1) {
        cout << "brand storage price\n";
    } else if (choice == 2) {
        cout << "name calories price\n";
    } else if (choice == 3) {
        cout << "title pages price\n";
    } else if (choice == 4) {
        cout << "size color price\n";
    }

    p->input();
    return p;
}

void printMenu() {
    cout << "\n=== Order Management Menu ===\n";
    cout << "1) Add product to current order\n";
    cout << "2) Add current order to the main list\n";
    cout << "3) Start new order\n";
    cout << "4) View all orders\n";
    cout << "5) Remove a completed order\n";
    cout << "6) Exit (save backup and quit)\n";
    cout << "Choice: ";
}

int main() {
    list<Order> orders;
    Order currentOrder;
    bool orderHasName = false;

    const string backupFile = "orders.txt";
    loadOrders(orders, backupFile);

    while (true) {
        printMenu();
        int option;
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');

        if (option == 1) {
            if (!orderHasName) {
                cout << "Enter customer name for current order: ";
                string name;
                getline(cin, name);
                currentOrder.setCustomerName(name);
                orderHasName = true;
            }
            Product* product = createProductByMenu();
            if (product) {
                currentOrder.addItem(product);
                cout << "Product added to order.\n";
            } else {
                cout << "Product not added.\n";
            }
        } else if (option == 2) {
            if (!currentOrder.hasItems()) {
                cout << "Current order has no items. Add items first.\n";
                continue;
            }
            if (!orderHasName) {
                cout << "Enter customer name for current order: ";
                string name;
                getline(cin, name);
                currentOrder.setCustomerName(name);
                orderHasName = true;
            }
            orders.push_back(currentOrder);
            currentOrder = Order();
            orderHasName = false;
            cout << "Order added to main list.\n";
        } else if (option == 3) {
            if (currentOrder.hasItems()) {
                cout << "Current order has items. Add it to list before starting a new one? (y/n): ";
                string answer;
                getline(cin, answer);
                if (!answer.empty() && (answer[0] == 'y' || answer[0] == 'Y')) {
                    if (!orderHasName) {
                        cout << "Enter customer name for current order: ";
                        string name;
                        getline(cin, name);
                        currentOrder.setCustomerName(name);
                        orderHasName = true;
                    }
                    orders.push_back(currentOrder);
                    cout << "Saved current order.\n";
                }
            }
            currentOrder = Order();
            orderHasName = false;
            cout << "Started a new order.\n";
        } else if (option == 4) {
            if (orders.empty()) {
                cout << "No orders available.\n";
            }
            int idx = 1;
            for (const Order& o : orders) {
                cout << "Order #" << idx++ << "\n";
                o.output();
            }
        } else if (option == 5) {
            if (orders.empty()) {
                cout << "No orders to remove.\n";
                continue;
            }
            cout << "Enter order number to remove (1-" << orders.size() << "): ";
            int rem;
            cin >> rem;
            cin.ignore(1000, '\n');
            if (rem < 1 || rem > (int)orders.size()) {
                cout << "Invalid order number.\n";
                continue;
            }
            auto it = orders.begin();
            advance(it, rem - 1);
            orders.erase(it);
            cout << "Order removed.\n";
        } else if (option == 6) {
            saveOrders(orders, backupFile);
            cout << "Saved orders to " << backupFile << " and exiting.\n";
            break;
        } else {
            cout << "Invalid menu option.\n";
        }
    }

    return 0;
}
