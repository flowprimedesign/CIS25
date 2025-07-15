/*
    PROGRAM: Assignment 12 - Working with Kaggle Datasets
    Written by Luis Ibarra
    Description: A program that demonstrates how to work with Kaggle datasets in C++ using a class-based approach.
    Last modified: 7/15/25
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class F1DataAnalyzer {
private:
    vector<vector<string>> data;
    vector<string> headers;
    string filename;
    
public:
    // Constructor
    F1DataAnalyzer(const string& file) : filename(file) {}
    
    // Load CSV data from file
    bool loadData() {
        ifstream file(filename);
        string line;
        
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return false;
        }
        
        cout << "Reading F1 2022 data from CSV file..." << endl;
        
        // Read header line
        if (getline(file, line)) {
            stringstream ss(line);
            string header;
            while (getline(ss, header, ',')) {
                headers.push_back(header);
            }
        }
        
        // Read data lines
        while (getline(file, line)) {
            vector<string> row;
            stringstream ss(line);
            string cell;
            
            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            
            if (!row.empty()) {
                data.push_back(row);
            }
        }
        
        file.close();
        return true;
    }
    
    // Display headers
    void displayHeaders() {
        // Create abbreviated headers for better alignment
        vector<string> abbrevHeaders = {"POS", "CODE", "DRIVER", "TEAM", "PTS", "POLES", "F.LAPS", "WINS", "PODIUMS", "DNFS"};
        
        for (size_t i = 0; i < abbrevHeaders.size() && i < headers.size(); i++) {
            cout << abbrevHeaders[i];
            if (i < abbrevHeaders.size() - 1) cout << " | ";
        }
        cout << endl;
        cout << string(70, '-') << endl;
    }
    
    // Display first N rows of data
    void displayData(int numRows = 10) {
        displayHeaders();
        
        int rowsToShow = min(numRows, (int)data.size());
        for (int i = 0; i < rowsToShow; i++) {
            for (size_t j = 0; j < data[i].size(); j++) {
                cout << data[i][j];
                if (j < data[i].size() - 1) cout << " | ";
            }
            cout << endl;
        }
        
        cout << string(70, '-') << endl;
        cout << "Displayed " << rowsToShow << " of " << data.size() << " total rows." << endl;
    }
    
    // Get number of rows loaded
    int getRowCount() const {
        return data.size();
    }
    
    // Find driver with most points
    void findMostPoints() {
        if (data.empty()) return;
        
        int maxPoints = 0;
        string driverName = "", driverCode = "", team = "";
        
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].size() > 4) {
                int points = stoi(data[i][4]); // Points column
                if (points > maxPoints) {
                    maxPoints = points;
                    driverName = data[i][2]; // Driver name
                    driverCode = data[i][1]; // Driver code
                    team = data[i][3];       // Team
                }
            }
        }
        
        cout << "Most Points: " << driverName << " (" << driverCode << ") - " << team << " - " << maxPoints << " points" << endl;
    }
    
    // Find driver with most wins
    void findMostWins() {
        if (data.empty()) return;
        
        int maxWins = 0;
        string driverName = "", driverCode = "", team = "";
        
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].size() > 7) {
                int wins = stoi(data[i][7]); // Wins column
                if (wins > maxWins) {
                    maxWins = wins;
                    driverName = data[i][2]; // Driver name
                    driverCode = data[i][1]; // Driver code
                    team = data[i][3];       // Team
                }
            }
        }
        
        cout << "Most Wins: " << driverName << " (" << driverCode << ") - " << team << " - " << maxWins << " wins" << endl;
    }
    
    // Find driver with most pole positions
    void findMostPoles() {
        if (data.empty()) return;
        
        int maxPoles = 0;
        string driverName = "", driverCode = "", team = "";
        
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].size() > 5) {
                int poles = stoi(data[i][5]); // Pole Positions column
                if (poles > maxPoles) {
                    maxPoles = poles;
                    driverName = data[i][2]; // Driver name
                    driverCode = data[i][1]; // Driver code
                    team = data[i][3];       // Team
                }
            }
        }
        
        cout << "Most Pole Positions: " << driverName << " (" << driverCode << ") - " << team << " - " << maxPoles << " poles" << endl;
    }
    
    // Find driver with most fastest laps
    void findMostFastestLaps() {
        if (data.empty()) return;
        
        int maxFastestLaps = 0;
        string driverName = "", driverCode = "", team = "";
        
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].size() > 6) {
                int fastestLaps = stoi(data[i][6]); // Fastest Laps column
                if (fastestLaps > maxFastestLaps) {
                    maxFastestLaps = fastestLaps;
                    driverName = data[i][2]; // Driver name
                    driverCode = data[i][1]; // Driver code
                    team = data[i][3];       // Team
                }
            }
        }
        
        cout << "Most Fastest Laps: " << driverName << " (" << driverCode << ") - " << team << " - " << maxFastestLaps << " fastest laps" << endl;
    }
    
    // Find driver with most podiums
    void findMostPodiums() {
        if (data.empty()) return;
        
        int maxPodiums = 0;
        string driverName = "", driverCode = "", team = "";
        
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].size() > 8) {
                int podiums = stoi(data[i][8]); // Podiums column
                if (podiums > maxPodiums) {
                    maxPodiums = podiums;
                    driverName = data[i][2]; // Driver name
                    driverCode = data[i][1]; // Driver code
                    team = data[i][3];       // Team
                }
            }
        }
        
        cout << "Most Podiums: " << driverName << " (" << driverCode << ") - " << team << " - " << maxPodiums << " podiums" << endl;
    }
    
    // Find driver with most DNFs
    void findMostDNFs() {
        if (data.empty()) return;
        
        int maxDNFs = 0;
        string driverName = "", driverCode = "", team = "";
        
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].size() > 9) {
                int dnfs = stoi(data[i][9]); // DNFs column
                if (dnfs > maxDNFs) {
                    maxDNFs = dnfs;
                    driverName = data[i][2]; // Driver name
                    driverCode = data[i][1]; // Driver code
                    team = data[i][3];       // Team
                }
            }
        }
        
        cout << "Most DNFs: " << driverName << " (" << driverCode << ") - " << team << " - " << maxDNFs << " DNFs" << endl;
    }
};

int main() {
    // Create F1 data analyzer object
    F1DataAnalyzer analyzer("F1_2022_data.csv");
    
    // Load the data
    if (!analyzer.loadData()) {
        return 1;
    }
    
    // Display first 15 rows
    analyzer.displayData(15);
    
    // Extract and display the 6 data fields
    cout << "\n=== F1 2022 Season Leaders ===" << endl;
    cout << string(50, '=') << endl;
    
    analyzer.findMostPoints();
    analyzer.findMostWins();
    analyzer.findMostPoles();
    analyzer.findMostFastestLaps();
    analyzer.findMostPodiums();
    analyzer.findMostDNFs();
    
    cout << string(50, '=') << endl;
    
    return 0;
}