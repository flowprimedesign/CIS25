#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
using namespace std;

class Item {
private:
    string name;
    int quantity;

public:
    Item();
    Item(string itemName, int itemQty);
    void display();
};

#endif
