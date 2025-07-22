/*
    PROGRAM: Midterm - 
    Written by Luis Ibarra
    Description: A program that simulates a bank account app while demonstrating the use of classes,
     dynamic memory allocation, pointers, binary search, and file I/O in C++.
     The program shows a series of menus for user login (file I/O), banking operations, and item purchases,
     including a search feature for items by ID.
    Last modified: 7/22/25
*/

#include <iostream> 
#include <fstream> 
#include <string> 

using namespace std; 

// CLI Menus
// First menu - Sign in or Create User
int displayLoginMenu() {
    int choice;
    cout << "\n=== Welcome to Bank Account Simulation ===" << endl;
    cout << "Choose an option: " << endl; 
    cout << "1. Sign In\n2. Create New Username\n3. Exit\n"; 
    cout << "Enter choice: ";
    cin >> choice; 
    return choice;
}

// Second menu - Banking operations
int displayBankMenu() {
    int choice;
    cout << "\n=== Banking Menu ===" << endl;
    cout << "1. Deposit Money\n2. View Balance\n3. Make Purchase\n4. View Transaction Log\n5. Logout\n";
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

// Third menu - Purchase operations
int displayPurchaseMenu() {
    int choice;
    cout << "\n=== Purchase Menu ===" << endl;
    cout << "1. iPhone (ID: 101) - $25\n2. Computer (ID: 102) - $35\n3. Scooter (ID: 103) - $39\n4. Tablet (ID: 104) - $29\n5. Headphones (ID: 105) - $15\n6. Search by ID\n7. Go back\n";
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}
// Class User simulates user creation and login
// Define a struct to represent a user
struct User {
    int id;
    string username;
    double myaccount;
};
// ofstream / ifstream to simulate creating new user and signing in
// Save new user data to file
void saveUserToFile(User user) { 
    ofstream out("username.txt"); 
    if (out.is_open()) { 
        out << user.id << "," << user.username << "," << user.myaccount << endl; 
        out.close(); 
        cout << "User saved to file." << endl; 
    } else { 
        cout << "Unable to open file for writing." << endl; 
    } 
} 
// Load and display data from file 
bool loadUserFromFile() { 
    ifstream in("username.txt"); 
    if (in.is_open()) { 
        string line; 
        if (getline(in, line)) {
            cout << "User data: " << line << endl; 
            in.close();
            return true; // Successfully loaded user data
        } else {
            cout << "User file is empty." << endl;
            in.close();
            return false; // File exists but is empty
        }
    } else { 
        cout << "No user found. Please create a new user first." << endl; 
        return false; // File doesn't exist
    } 
}

// class BankAccount keeps balances and saves transactions to .txt file
class BankAccount {
    private:
        double balance;
    
    public:
        BankAccount() {
            loadBalance();
        }

    // Method for depositing money
        void deposit(double amount) {
            balance += amount;
            saveBalance();
            saveTransaction("Deposit", amount);
            cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
        }
    // Method for making a purchase
        void makePurchase(string item, double cost) {
            if (cost > balance) {
                cout << "Insufficient funds for " << item << endl;
                cout << "Current balance: $" << balance << ", Cost: $" << cost << endl;
            } else {
                balance -= cost;
                saveBalance();
                saveTransaction("Purchase - " + item, cost);
                cout << "Purchased " << item << " for $" << cost << ". New balance: $" << balance << endl;
            }
        }
    // Method for displaying balance
        void displayBalance() {
            cout << "Current Balance: $" << balance << endl;
        }
    // Method for viewing transaction log
    // reads transactions from a .txt file 
        void viewTransactionLog() {
            cout << "\n=== Transaction Log ===" << endl;
            ifstream file("transactions.txt");
            if (file.is_open()) {
                string line;
                if (file.peek() == ifstream::traits_type::eof()) {
                    cout << "No transactions found." << endl;
                } else {
                    while (getline(file, line)) {
                        cout << line << endl;
                    }
                }
                file.close();
            } else {
                cout << "No transaction log found." << endl;
            }
            cout << "======================" << endl;
        }
    // Method for saving transactions to transactions.txt file
    // updated every time a transaction occurs including deposists and purchases
        void saveTransaction(string type, double amount) {
            ofstream file("transactions.txt", ios::app);
            if (file.is_open()) {
                file << type << ": $" << amount << endl;
                file.close();
            }
        }
    // Method for saving balance to transactions.txt file
        void saveBalance() {
            ofstream file("transactions.txt", ios::app);
            if (file.is_open()) {
                file << "Balance: $" << balance << endl;
                file.close();
            }
        }
    // Method for loading balance from transactions.txt file
        void loadBalance() {
            ifstream file("transactions.txt");
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    if (line.find("Balance: $") != string::npos) {
                        balance = stod(line.substr(10)); // Extract balance value after "Balance: $"
                    }
                }
                file.close();
            } else {
                balance = 0.0; // Default if no file exists
            }
        }
    };


//class Item using different data types for storeitems
class Item { 
    public: 
       string name; 
       double cost;
       int id;
};
//binary search for storeitem by ID
int binarySearch(Item* items, int size, int targetId) {
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

    // Welcome message
    cout << "Welcome to the Bank account Simulation!\n";
    cout << "You can sign in, view your balance, make purchase from online store, search online store\n";

    // Two-step CLI system
    bool running = true;
    
    while (running) {
        // Login just means reading from the created file with user data
        int loginChoice = displayLoginMenu();
        
        if (loginChoice == 1) {
            cout << "Attempting to sign in...\n";
            if (loadUserFromFile()) { // Only proceed if user data was successfully loaded
                cout << "User signed in successfully!\n";
                
                // Second menu - Banking operations
                BankAccount myAccount;
                bool loggedIn = true;
            
            while (loggedIn) {
                int bankChoice = displayBankMenu();
                
                switch (bankChoice) {
                    case 1: {
                        double amount;
                        cout << "Enter deposit amount: $";
                        cin >> amount;
                        myAccount.deposit(amount);
                        break;
                    }
                    case 2:
                    // calls balance and adds it tor transactions.txt
                        myAccount.displayBalance();
                        break;
                    case 3: {
                        // Purchase menu with search functionality
                        bool inPurchaseMenu = true;
                        
                        // Initialize store items for search
                        // Dynamically allocate memory for store items
                        // Using an array to represent items in the store
                        int size = 5;
                        Item* storeItems = new Item[size];
                        
                        // Initialize each item properly
                        storeItems[0].id = 101; storeItems[0].name = "iPhone"; storeItems[0].cost = 25;
                        storeItems[1].id = 102; storeItems[1].name = "Computer"; storeItems[1].cost = 35;
                        storeItems[2].id = 103; storeItems[2].name = "Scooter"; storeItems[2].cost = 39;
                        storeItems[3].id = 104; storeItems[3].name = "Tablet"; storeItems[3].cost = 29;
                        storeItems[4].id = 105; storeItems[4].name = "Headphones"; storeItems[4].cost = 15;

                        while (inPurchaseMenu) {
                            int purchaseChoice = displayPurchaseMenu();
                            
                            switch (purchaseChoice) {
                                case 1:
                                    myAccount.makePurchase("iPhone", 25);
                                    break;
                                case 2:
                                    myAccount.makePurchase("Computer", 35);
                                    break;
                                case 3:
                                    myAccount.makePurchase("Scooter", 39);
                                    break;
                                case 4:
                                    myAccount.makePurchase("Tablet", 29);
                                    break;
                                case 5:
                                    myAccount.makePurchase("Headphones", 15);
                                    break;
                                case 6: {
                                    // Search functionality using binary search
                                    int searchId;
                                    cout << "Search for item by ID: ";
                                    cin >> searchId;
                                    
                                    int index = binarySearch(storeItems, size, searchId);
                                    if (index != -1) {
                                        cout << "Item found: ID=" << storeItems[index].id
                                             << ", Name=" << storeItems[index].name
                                             << ", Price=$" << storeItems[index].cost << endl;
                                        
                                        char buyChoice;
                                        cout << "Would you like to purchase this item? (y/n): ";
                                        cin >> buyChoice;
                                        if (buyChoice == 'y' || buyChoice == 'Y') {
                                            myAccount.makePurchase(storeItems[index].name, storeItems[index].cost);
                                        }
                                    } else {
                                        cout << "Item with ID " << searchId << " not found." << endl;
                                    }
                                    break;
                                }
                                case 7:
                                    cout << "Returning to banking menu...\n";
                                    inPurchaseMenu = false;
                                    break;
                                default:
                                    cout << "Invalid option.\n";
                            }
                        }
                        
                        delete[] storeItems; // Clean up memory
                        break;
                    }
                    case 4:
                        myAccount.viewTransactionLog();
                        break;
                    case 5:
                        cout << "Logging out...\n";
                        loggedIn = false;
                        break;
                    default:
                        cout << "Invalid option.\n";
                }
            }
            } else {
                cout << "Please create a new user account to continue.\n";
            }
            
        } else if (loginChoice == 2) {
            cout << "Creating new user...\n";
            User newUser;
            newUser.id = 1001; // Assign a default ID for the user
            cout << "Enter your Username: ";
            cin >> newUser.username;
            cout << "Enter initial deposit: $";
            cin >> newUser.myaccount;
            saveUserToFile(newUser); // Pass the User struct
            
            // Also save the initial deposit as balance to transactions.txt
            ofstream transactionFile("transactions.txt", ios::app);
            if (transactionFile.is_open()) {
                transactionFile << "Initial Deposit: $" << newUser.myaccount << endl;
                transactionFile << "Balance: $" << newUser.myaccount << endl;
                transactionFile.close();
            }
            
        } else if (loginChoice == 3) {
            cout << "Exiting...\n";
            running = false;
            
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0; 
}