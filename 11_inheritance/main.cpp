/*
    PROGRAM: Assignment 11 - Inheritance and Overriding with Header Files
    Written by Luis Ibarra
    Description: A program that demonstrates inheritance and method overriding in C++ using header files.
    Last modified: 7/15/25
*/

#include <iostream>
#include "User.h"
#include "Employee.h"
#include "InventoryManager.h"
using namespace std;

int main() {
    cout << "=== Access Level Demonstration ===" << endl;
    cout << endl;
    
    // Test polymorphism with base class pointers
    User* user1 = new User();
    User* user2 = new Employee();
    User* user3 = new InventoryManager();
    
    cout << "User object: ";
    user1->accessLevel();
    
    cout << "Employee object (via User pointer): ";
    user2->accessLevel();
    
    cout << "InventoryManager object (via User pointer): ";
    user3->accessLevel();
    
    cout << endl;
    cout << "=== Direct Object Calls ===" << endl;
    
    // Test with direct objects
    User regularUser;
    Employee emp;
    InventoryManager mgr;
    
    cout << "Regular User: ";
    regularUser.accessLevel();
    
    cout << "Employee: ";
    emp.accessLevel();
    
    cout << "Inventory Manager: ";
    mgr.accessLevel();
    
    // Clean up dynamic memory
    delete user1;
    delete user2;
    delete user3;
    
    return 0;
}
