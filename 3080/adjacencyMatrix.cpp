/*
Purpose of the Program: Flight Route Lookup System
This C++ program simulates a flight route system using an adjacency matrix to represent direct flight connections between cities. The program allows users to:
1. View the adjacency matrix of flight routes between four cities: "NYC", "LAX", "ORD", and "DFW".
2. Check if a direct flight exists between two cities by entering their names.
3. Repeat the process for multiple flight queries.
*/

#include <iostream>
#include <map>
using namespace std;

const int CITY_COUNT = 4;  // Number of cities

void displayMatrix(int matrix[][CITY_COUNT], string cities[]);
void checkFlight(int matrix[][CITY_COUNT], string cities[], map<string, int> cityIndex);

int main() {
    // List of cities
    string cities[CITY_COUNT] = {"NYC", "LAX", "ORD", "DFW"};

    // Map city names to their indices
    map<string, int> cityIndex;
    for (int i = 0; i < CITY_COUNT; i++) {
        cityIndex[cities[i]] = i;
    }
    /*
    In C++, a map is a standard library container that stores key-value pairs in sorted order by key. 
    It allows you to efficiently look up, insert, and delete elements based on a unique key.
    */

    // Adjacency matrix for flight routes
    int flightMatrix[CITY_COUNT][CITY_COUNT] = {
        {0, 1, 1, 0},  // NYC -> LAX, NYC -> ORD
        {1, 0, 1, 0},  // LAX -> NYC, LAX -> ORD
        {1, 1, 0, 1},  // ORD -> NYC, ORD -> LAX, ORD -> DFW
        {0, 0, 1, 0}   // DFW -> ORD
    };

    // Display the flight routes matrix
    displayMatrix(flightMatrix, cities);

    // Allow user to check for direct flights
    char choice;
    do {
        checkFlight(flightMatrix, cities, cityIndex);
        cout << "\nWould you like to check another flight? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}


// Function to display the adjacency matrix
void displayMatrix(int matrix[][CITY_COUNT], string cities[]) {
    cout << "Flight Routes Adjacency Matrix:" << endl;
    cout << "     ";  
    for (int i = 0; i < CITY_COUNT; i++) {
        cout << cities[i] << "  ";
    }
    cout << endl;

    for (int i = 0; i < CITY_COUNT; i++) {
        cout << cities[i] << "  ";
        for (int j = 0; j < CITY_COUNT; j++) {
            cout << "  " << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a direct flight exists using city names
void checkFlight(int matrix[][CITY_COUNT], string cities[], map<string, int> cityIndex) {
    string city1, city2;
    cout << "\nEnter the first city: ";
    cin >> city1;
    cout << "Enter the second city: ";
    cin >> city2;

    // Convert city names to indices
    if (cityIndex.find(city1) == cityIndex.end() || cityIndex.find(city2) == cityIndex.end()) {
        cout << "Invalid city names. Please enter valid cities." << endl;
        return;
    }

    int index1 = cityIndex[city1];
    int index2 = cityIndex[city2];

    if (matrix[index1][index2] == 1) {
        cout << "Yes! Direct flight available between " << city1 << " and " << city2 << endl;
    } else {
        cout << "No! No direct flight between " << city1 << " and " << city2 << endl;
    }
}
