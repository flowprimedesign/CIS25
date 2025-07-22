/*
    PROGRAM: Assignment 10 - Header Files
    Written by Luis Ibarra
    Description: A program that demonstrates the use of header files in C++.
    Last modified: 7/15/25
*/

#include <iostream>
#include "Item.h"
using namespace std;

int main() {
    Item item1("Notebook", 10);
    Item item2("Pencil", 50);

    item1.display();
    item2.display();

    return 0;
}

