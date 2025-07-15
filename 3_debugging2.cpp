/*
    PROGRAM: Assignment 3.2 - Debugging / Output highest of three inputs
    Written by Luis Ibarra
    Description: A program that asks the user to input three numbers and outputs the largest of 
    the three.
    Last modified: 6/18/25
*/

#include <iostream>

using namespace std;

int main() {
    float n1, n2 ,n3;

    cout << "Please Enter three numbers: " << endl;
    cin >> n1 >> n2 >> n3;

    if(n1 >= n2 && n1 >= n3){
        cout << "The Largest number is: " << n1 << endl;
    } else if 
        (n2 >= n1 && n2 >= n3)
    {     cout << "The Largest number is: " << n2 << endl;
    } else if 
        (n3 >= n1 && n3 >= n2)
    {
        cout << "The Largest number is: " << n3 << endl;
    }
    
    return 0;
}   
