/*
    PROGRAM: Assignment 3.1 - Debugging and Switch Case Example
    Written by Luis Ibarra
    Description: A program that use a switch case statement for a simple menu.
    Last modified: 6/18/25
*/

#include <iostream>

using namespace std;

int main() {
    int choice; 

    cout << "Choose an option: " << endl; 
	cout << "1. Add Item\n2. View Items\n3. Exit\n"; 
	
	cin >> choice; 

	if (choice == 1) cout << "Item added!\n"; 
	else if (choice == 2) cout << "Displaying items...\n"; 
	else if (choice == 3) cout << "Exiting...\n"; 
	else cout << "Invalid option.\n"; 
	return 0; 
} 