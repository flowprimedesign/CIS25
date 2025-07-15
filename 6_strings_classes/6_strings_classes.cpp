/*
    PROGRAM: Assignment 6 - Strings and Classes
    Written by Luis Ibarra
    Description: A program that uses a class to manage an item with a name and quantity,
    and saves the item to a file. It also includes functionality to load and display data from the file.
    Last modified: 6/29/25
*/

#include <iostream> 
#include <fstream> 
#include <string> 
using namespace std; 

class Item { 
public: 
   string name; 
   int quantity;
 

   void saveToFile() { 
    ofstream out("items.txt"); 
    if (out.is_open()) { 
        out << name << "," << quantity << endl; 
        out.close(); 
        cout << "Item saved to file." << endl; 
    } else { 
        cout << "Unable to open file for writing." << endl; 
    } 
} 
// Load and display data from file 
void loadFromFile() { 
    ifstream in("items.txt"); 
    if (in.is_open()) { 
        string line; 
        while (getline(in, line)) { 
            cout << "File content: " << line << endl; 
        } 
        in.close(); 
    } else { 
        cout << "Unable to open file for reading." << endl; 
    } 
} };

int main() { 

    Item tool; 
    tool.name = "Screwdriver"; 
    tool.quantity = 10; 

    tool.saveToFile(); 
    tool.loadFromFile(); // Optional 

    return 0; 
}