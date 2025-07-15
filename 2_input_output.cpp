/*
    PROGRAM: Assignment 2 - Input/Output Example
    Written by Luis Ibarra
    Description: A program that takes user input for an item name, quantity, and cost, 
    then calculates and displays the total cost.
    Last modified: 6/18/25
*/

#include <iostream>
#include <string>

using namespace std;

int main() {

    string itemName; 
	int quantity; 
	float cost; 

    // input section
    cout << "Welcome to the Cost Calculator!\n";
	cout << "Please Enter item name: "; 
	cin >> itemName; 
	cout << "Enter quantity: "; 
	cin >> quantity; 
	cout << "Enter cost: "; 
	cin >> cost;

    // total output
	cout << "Total cost for " << itemName << ": $" << (quantity * cost) << endl; 
	return 0; 
} 