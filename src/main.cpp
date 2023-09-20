#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Account.h" // Include your member class header file
#include "Member.h" // Include your member class header file
#include "Motorbike.h" // Include your motorbike class header file
#include "Admin.h" // Include your admin class header file
#include "Location.h" // Include your Location class header file
#include "RentalRequest.h" // Include your Location class header file

using namespace std;

class MotorbikeRentalApp {
private:
    vector<Member> members; // Vector to store member objects
    vector<Motorbike> motorbikes; // Vector to store motorbike objects
    vector<Location> locations;
    vector<RentalRequest> rentarRequests;
    Admin admin; // Admin object to manage the system
    Account currentAccount;

public:
    MotorbikeRentalApp() {
        // Load data from the appdata.txt file (if available)
        loadData();
    }

    void run() {
        int choice;
        do {
            displayWelcomeScreen();
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear newline from the input buffer

            switch (choice) {
                case 1:
                    // Handle guest functionality
                    handleGuestMenu();
                    break;
                case 2:
                    handleMemberMenu();
                    break;
                case 3:
                    handleAdminMenu();
                    break;
                case 0:
                    // Save data to the appdata.txt file before exiting
                    saveData();
                    cout << "Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 0);
    }

    // Add member, motorbike, and admin management functions here

    void loadData() {
        // Load data from the appdata.txt file into members, motorbikes, and admin
        ifstream file("appdata.txt");
        if (file.is_open()) {
            // Read data and create objects
            // Populate members and motorbikes vectors
            // Initialize admin object
            file.close();
        }
    }

    void saveData() {
        // Save data from members, motorbikes, and admin to the appdata.txt file
        ofstream file("appdata.txt");
        if (file.is_open()) {
            // Write data for members and motorbikes
            // Write data for admin
            file.close();
        }
    }

    void displayWelcomeScreen() {
        // Display welcome screen with options for guest, member, and admin
        cout << "Welcome to the Motorbike Rental Application!" << endl;
        // Add content here
    }

    void handleMemberMenu() {
        // Implement member-specific menu options and actions
        // Include login, listing motorbike, requesting rental, etc.
    }

    void handleAdminMenu() {
        // Implement admin-specific menu options and actions
        // Include viewing member and motorbike information, etc.
    }
    void handleGuestMenu() {
        // Implement admin-specific menu options and actions
        // Include viewing member and motorbike information, etc.
    }

    void listMotorbike() {

    }

    void listMotorbikeDetails() {

    }


};

int main() {
    MotorbikeRentalApp app;
    app.run();
    return 0;
}
