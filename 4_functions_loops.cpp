/*
    PROGRAM: Assignment 4 - Functions and Loops / Refactor menu using functions
    Written by Luis Ibarra
    Description: A program that uses functions and do-while loops for a simple menu.
    Last modified: 6/18/25
*/

#include <iostream>

using namespace std;

void showMenu(); // Function prototype

int main() { 
    int option; 

    do { 
        cout << "Choose an option: \n";
        showMenu(); 

        cin >> option; 

        if (option == 1) {
            cout << "Item added!\n";
        } else if (option == 2) {
            cout << "Displaying items...\n";
        } else if (option == 3) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid option. Please try again.\n";
        }

    } while (option != 3); 

    return 0; 
} 

void showMenu() { 
    cout << "1. Add\n2. View\n3. Exit\n"; 
} 