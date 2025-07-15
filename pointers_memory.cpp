/*
    PROGRAM: Week 2 Assignment 5 - Pointers and Memory Management
    Written by Luis Ibarra
    Description: A program that uses pointers and dynamic memory allocation to manage an array of structs representing students.
    This program includes a binary search function to find a student by ID.
    Last modified: 6/29/25
*/

#include <iostream> 
#include <string> 
 using namespace std;

// Define a struct to represent a student 
struct Student { 
 int id; 
 string name; 
 double gpa; 
}; 

//binary search for item
int binarySearch(Student* items, int size, int targetId) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (items[mid].id == targetId)
            return mid;
        else if (items[mid].id < targetId)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Not found
}

int main() { 
int size = 5;
Student* students = new Student[size]; // Dynamically allocate array

 // Initialize the elements of the array 
students[0] = {101, "Michael", 3.8}; 
students[1] = {102, "Lakisha", 3.5}; 
students[2] = {103, "Charlie", 3.9};
students[3] = {104, "Alice", 3.6}; 
students[4] = {105, "Bob", 3.7};


 // Ask user for ID to search
 int searchId;
 cout << "Enter item ID to search for: ";
 cin >> searchId;

 int index = binarySearch(students, size, searchId);
 if (index != -1) {
     cout << "Student found: ID=" << students[index].id
          << ", Name=" << students[index].name
          << ", GPA=" << students[index].gpa << endl;
 } else {
     cout << "Student with ID " << searchId << " not found." << endl;
 }


 // Access and print data from the array of structs 
//  for (int i = 0; i < 3; ++i) { 
//  cout << "Student ID: " << students[i].id  
// << ", Name: " << students[i].name  
// << ", GPA: " << students[i].gpa << std::endl; 
//     } 

 delete[] students;

 return 0; 
} 


    
