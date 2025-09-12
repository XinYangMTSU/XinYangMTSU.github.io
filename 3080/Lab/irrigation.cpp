/*
This program simulates a smart irrigation system that evaluates whether irrigation 
should be activated based on two factors: 
the dryness of the soil and whether rain is expected.

Decision-Making:

The irrigation system should only be activated if:
    The soil is dry (soilDry = true) AND
    Rain is not expected (rainExpected = false)    
*/

#include <iostream>
using namespace std;


//function prototype
bool shouldIrrigate(bool soilDry, bool rainExpected);


int main() {

    //varaible declaration
    bool soilDry, rainExpected;
    char choice;

    cout << "Smart Irrigation System\n";
    cout << "----------------------------------------\n";

    do {
        // Input soilDry from the user
        cout << "Is the soil dry? (1 for Yes, 0 for No): ";
        cin >> soilDry;

        // Input rainExpected from the user
        cout << "Is rain expected? (1 for Yes, 0 for No): ";
        cin >> rainExpected;

        // Determine if irrigation system should activate
        if (shouldIrrigate(soilDry, rainExpected)) {
            cout << "The irrigation system is ACTIVATED.\n";
        } else {
            cout << "The irrigation system remains OFF.\n";
        }

        // Ask user if they want to evaluate another scenario
        cout << "Do you want to evaluate another scenario? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "System evaluation ended. Thank you!\n";
    cout << "----------------------------------------\n";
    return 0;
}


// Function to determine if the irrigation system should activate
bool shouldIrrigate(bool soilDry, bool rainExpected) {
    return soilDry && !rainExpected; // Activate if soil is dry and no rain is expected
}

