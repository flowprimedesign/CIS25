/*
    PROGRAM: Assignment 7 - OOP and Inheritance
    Written by Luis Ibarra
    Description: A program that demonstrates the use of inheritance in C++ by creating a base class Item and derived classes Perishable 
    and NonPerishable.
    Last modified: 6/29/25
*/

#include <iostream>
#include <string>
using namespace std;

// Base class
class Item {
public:
    string name;
    int quantity;

    Item(string n, int q) {
        name = n;
        quantity = q;
    }

    virtual ~Item() {} // Virtual destructor cleanup
    virtual void display() = 0; // Pure virtual function
};
// Perishable item
class Perishable : public Item {
    public:
        Perishable(string n, int q) : Item(n, q) {}
    
        void display() override {
            cout << name << " (Perishable), Qty: " << quantity << endl;
        }
    };
    
    // Non-Perishable item
    class NonPerishable : public Item {
    public:
        NonPerishable(string n, int q) : Item(n, q) {}
    
        void display() override {
            cout << name << " (Non-Perishable), Qty: " << quantity << endl;
        }
    };

    int main() {
        // Create inventory using base class pointers
        Item* item1 = new Perishable("Milk", 10);
        Item* item2 = new NonPerishable("Cereal", 20);
        Item* item3 = new Perishable("Eggs", 12);
        Item* item4 = new NonPerishable("Rice", 30);
    
        // Display items
        cout << "Inventory Items:" << endl;
        cout << "-----------------" << endl;
        item1->display();
        item2->display();
        item3->display();
        item4->display();
    
        // Clean up
        delete item1;
        delete item2;
        delete item3;
        delete item4;
    
        return 0;
    }
    