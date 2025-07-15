# CIS25 - C++ Programming Course

**Student:** Luis Ibarra  
**Course:** Computer Information Systems 25  
**Institution:** BCC (Berkeley City College)  
**Last Updated:** July 15, 2025

## Course Overview

This repository contains all programming assignments for CIS25, demonstrating fundamental to advanced C++ programming concepts including basic syntax, object-oriented programming, inheritance, file I/O, and data analysis.

## Project Structure

```
cis25/
├── 1_hello_inventory.cpp              # Assignment 1: Hello World & Data Types
├── 2_input_output.cpp                 # Assignment 2: Input/Output Operations
├── 3_debugging.cpp                    # Assignment 3.1: Debugging & Menu System
├── 3_debugging2.cpp                   # Assignment 3.2: Find Largest of Three Numbers
├── 4_functions_loops.cpp              # Assignment 4: Functions & Do-While Loops
├── 5_pointers_memory.cpp              # Assignment 5: Pointers & Dynamic Memory
├── 6_strings_classes/                 # Assignment 6: String Handling & File I/O
│   ├── 6_strings_classes.cpp          # Main program file
│   └── items.txt                      # Item data file
├── 7_object.cpp                       # Assignment 7: OOP & Inheritance Basics
├── 8_bankSim/                         # Assignment 8: Bank Account Simulation
│   ├── 8_bankSim.cpp                  # Main program file
│   └── transactions.txt               # Bank transaction log file
├── 9_inventory_array.cpp              # Assignment 9: Array-Based Inventory System
├── 10_inventoryProject/               # Assignment 10: Header Files Project
│   ├── main.cpp                       # Main program file
│   ├── Item.h                         # Item class header
│   └── Item.cpp                       # Item class implementation
├── 11_inheritance/                    # Assignment 11: Advanced Inheritance
│   ├── main.cpp                       # Main program demonstrating inheritance
│   ├── User.h                         # Base User class header
│   ├── User.cpp                       # Base User class implementation
│   ├── Employee.h                     # Employee class header (inherits User)
│   ├── Employee.cpp                   # Employee class implementation
│   ├── InventoryManager.h             # InventoryManager class header
│   └── InventoryManager.cpp           # InventoryManager class implementation
└── 12_kaggle_dataset/                 # Assignment 12: Dataset Analysis
    ├── 12_kaggle_dataset.cpp          # F1 2022 data analyzer with class structure
    └── F1_2022_data.csv               # F1 2022 season dataset
```

## Assignment Details

### Assignment 1 - Hello Inventory System

**File:** `1_hello_inventory.cpp`

- **Concepts:** Basic C++ syntax, data types, sizeof operator
- **Features:** Welcome message, data type size demonstration

### Assignment 2 - Input/Output Example

**File:** `2_input_output.cpp`

- **Concepts:** User input, string handling, basic calculations
- **Features:** Cost calculator for inventory items

### Assignment 3.1 - Debugging & Menu System

**File:** `3_debugging.cpp`

- **Concepts:** Conditional statements, menu-driven programming
- **Features:** Simple 3-option menu with if-else logic

### Assignment 3.2 - Find Largest Number

**File:** `3_debugging2.cpp`

- **Concepts:** Conditional logic, multiple comparisons
- **Features:** Finds the largest of three input numbers

### Assignment 4 - Functions & Loops

**File:** `4_functions_loops.cpp`

- **Concepts:** Function prototypes, do-while loops, modular programming
- **Features:** Menu system using functions and loops

### Assignment 5 - Pointers & Memory Management

**File:** `5_pointers_memory.cpp`

- **Concepts:** Dynamic memory allocation, structs, binary search
- **Features:** Student database with search functionality

### Assignment 6 - Strings & Classes

**Directory:** `6_strings_classes/`

- **Concepts:** Basic classes, file I/O, string manipulation
- **Features:** Item class with file save/load capabilities
- **Files:**
  - `6_strings_classes.cpp` - Main program
  - `items.txt` - Item data file

### Assignment 7 - Object-Oriented Programming

**File:** `7_object.cpp`

- **Concepts:** Inheritance, virtual functions, polymorphism
- **Features:** Item hierarchy (Perishable/NonPerishable)

### Assignment 8 - Bank Account Simulation

**Directory:** `8_bankSim/`

- **Concepts:** Class design, file I/O, transaction logging
- **Features:** Banking operations with transaction history
- **Files:**
  - `8_bankSim.cpp` - Main program
  - `transactions.txt` - Transaction log file

### Assignment 9 - Inventory Array Management

**File:** `9_inventory_array.cpp`

- **Concepts:** Arrays, linear search, interactive input
- **Features:** Array-based inventory with search functionality

### Assignment 10 - Header Files Project

**Directory:** `10_inventoryProject/`

- **Concepts:** Header files, separate compilation, project organization
- **Features:** Multi-file C++ project structure
- **Files:**
  - `main.cpp` - Main program
  - `Item.h` - Class declaration
  - `Item.cpp` - Class implementation

### Assignment 11 - Advanced Inheritance

**Directory:** `11_inheritance/`

- **Concepts:** Multi-level inheritance, method overriding, polymorphism
- **Features:** Access control system with three user levels
- **Class Hierarchy:** User → Employee → InventoryManager
- **Files:**
  - `main.cpp` - Demonstration program
  - `User.h/.cpp` - Base class
  - `Employee.h/.cpp` - Derived class
  - `InventoryManager.h/.cpp` - Further derived class

### Assignment 12 - Kaggle Dataset Analysis

**Directory:** `12_kaggle_dataset/`

- **Concepts:** CSV parsing, data analysis, vector containers
- **Features:** F1 2022 season data analysis with statistical leaders
- **Files:**
  - `12_kaggle_dataset.cpp` - Data analyzer class
  - `F1_2022_data.csv` - Formula 1 2022 season dataset

## Compilation Instructions

### Single File Programs (Assignments 1-5, 7, 9)

```bash
g++ -o program_name assignment_file.cpp
./program_name
```

### Multi-File Projects

#### Assignment 6 - Strings & Classes

```bash
cd 6_strings_classes
g++ -o strings_classes 6_strings_classes.cpp
./strings_classes
```

#### Assignment 8 - Bank Simulation

```bash
cd 8_bankSim
g++ -o bankSim 8_bankSim.cpp
./bankSim
```

#### Assignment 10 - Header Files

```bash
cd 10_inventoryProject
g++ -o inventory main.cpp Item.cpp
./inventory
```

#### Assignment 11 - Inheritance

```bash
cd 11_inheritance
g++ -o inheritance main.cpp User.cpp Employee.cpp InventoryManager.cpp
./inheritance
```

#### Assignment 12 - Dataset Analysis

```bash
cd 12_kaggle_dataset
g++ -o kaggle_analyzer 12_kaggle_dataset.cpp
./kaggle_analyzer
```

## Dataset Information

### F1 2022 Season Data (`F1_2022_data.csv`)

- **Source:** Kaggle dataset
- **Content:** Formula 1 2022 championship standings
- **Columns:** Position, Driver Code, Name, Team, Points, Poles, Fastest Laps, Wins, Podiums, DNFs
- **Total Drivers:** 22
- **Analysis Features:** Statistical leaders in various categories
