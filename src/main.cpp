#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Account.h"       // Include your member class header file
#include "Member.h"        // Include your member class header file
#include "Motorbike.h"     // Include your motorbike class header file
#include "Admin.h"         // Include your admin class header file
#include "RentalRequest.h" // Include your Location class header file

using namespace std;

class MotorbikeRentalApp
{
private:
    vector<Member> members;       // Vector to store member objects
    vector<Motorbike> motorbikes; // Vector to store motorbike objects

    Admin admin;

public:
    MotorbikeRentalApp()
    {
        // Load data from the appdata.txt file (if available)
        loadData();
    }

    void run()
    {
        int choice;
        do
        {
            displayWelcomeScreen();
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear newline from the input buffer

            switch (choice)
            {
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

    void loadData()
    {
        // Load data from the appdata.txt file into members, motorbikes, and admin
        ifstream file("appdata.txt");
        if (file.is_open())
        {
            // Read data and create objects
            // Populate members and motorbikes vectors
            // Initialize admin object
            file.close();
        }
    }

    void saveData()
    {
        // Save data from members, motorbikes, and admin to the appdata.txt file
        ofstream file("appdata.txt");
        if (file.is_open())
        {
            // Write data for members and motorbikes
            // Write data for admin
            file.close();
        }
    }

    void displayWelcomeScreen()
    {
        // Display welcome screen with options for guest, member, and admin
        cout << "EEET2482/COSC2082 ASSIGNMENT" << endl;
        cout << "MOTORBIKE RENTAL APPLICATION" << endl
             << endl;
        cout << "Instructor: Dr. Ling Huo Chong" << endl;
        cout << "Group: Group No." << endl;
        cout << "s3932112, Nguyen Nhat Minh" << endl;
        cout << "s39, Luu Quoc Nhat " << endl;
        cout << "s39, Luong Thao My" << endl;
        cout << "s39, Vu Tuan Linh" << endl
             << endl;
        cout << "USe the app as 1. Guest \t 2. Member \t 3. Admin" << endl;
    }

    void handleGuestMenu()
    {
        bool registered = false;
        while (!registered)
        {
            // Display guest menu options
            std::cout << "Guest Menu:" << std::endl;
            std::cout << "1. Register as a Member" << std::endl;
            std::cout << "2. View All Motorbike Details (without Reviews)" << std::endl;
            std::cout << "3. Exit" << std::endl;
            std::cout << "Enter your choice: ";

            int choice;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                Member::registerMember(members);
                std::cout << "Registration successful. Going back to main menu..." << std::endl;
                registered = true;
                break;
            }
            case 2:
            {
                // View all motorbike details
                listMotorbike();
                break;
            }
            case 3:
            {
                // Exit the guest menu
                return;
            }
            default:
            {
                std::cout << "Invalid choice. Please enter a valid option (1-3)." << std::endl;
                break;
            }
            }
        }
    }

    void handleMemberMenu()
    {
        // Login
        std::string username, password;
        bool isLogged = false;
        Member currentMember;

        std::cout << "Please enter your username: ";
        std::cin >> username;

        std::cout << "Please enter your password: ";
        std::cin >> password;

        for (Member &member : members)
        {
            if (member.getUsername() == username && member.checkPassword(password))
            {
                currentMember = member;
                isLogged = true;
                std::cout << "Login successful. Welcome, " << member.getFullName() << "!" << std::endl;
                break;
            }
        }
        if (!isLogged)
        {
            std::cout << "Login failed. Please check your username and password." << std::endl;
            std::cout << "Returning to menu...." << std::endl;
            return;
        }

        int choice;
        while (choice != 0)
        {
            std::cout << "\nMember Menu\n";
            std::cout << "1. View My Information\n";
            std::cout << "2. List My Motorbike\n";
            std::cout << "3. Unlist My Motorbike\n";
            std::cout << "4. Search for Available Motorbikes\n";
            std::cout << "5. Request to Rent a Motorbike\n";
            std::cout << "6. View Requests to My Motorbike\n";
            std::cout << "7. View My requests\n";
            std::cout << "8. Accept a Request\n";
            std::cout << "9. Rent Requested Motorbike\n";
            std::cout << "10. Rate Rented Motorbike\n";
            std::cout << "11. Rate Renters\n";
            std::cout << "12. View all motorbikes\n";
            std::cout << "0. Logout\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            // View information
                currentMember.viewMemberInfo();
                break;
            case 2:
            // List motorbike
                currentMember.listMotorbike();
                break;
            case 3:
            // Unlist motorbike
                currentMember.unlistMotorbike();
                break;
            case 4:   
            // Search Motorbike
                searchMotorbike(currentMember);
                break;
            case 5:
            // Request to rent motorbike
                // Implement requesting to rent a motorbike
                // You can prompt the member for details and handle the request.
                break;
            case 6:
                currentMember.viewRequests("1"); // View all rental requests
                break;
            case 7:
                // Implement accepting a request (rejecting others)
                // You can prompt the member to select a request to accept.
                break;
            case 8:
                // Implement renting the requested motorbike
                // You can prompt the member to confirm the rental.
                break;
            case 9:
                // Implement rating a rented motorbike
                // You can prompt the member to select a motorbike to rate.
                break;
            case 10:
                // Implement rating renters (members who rented the member's motorbike)
                // You can prompt the member to select a renter to rate.
                break;
            case 0:
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        };
    }

    void adminLogIn()
    {
        std::string username, password;

        std::cout << "Please enter your username: ";
        std::cin >> username;

        std::cout << "Please enter your password: ";
        std::cin >> password;

        if (username == "admin" && password == "admin")
        {

            std::cout << "Login successful. Welcome admin! " << std::endl;
        }
        else
        {
            std::cout << "Login failed. Please check your username and password." << std::endl;
        }
    }

    void handleAdminMenu()
    {
        // Implement admin-specific menu options and actions
        // Include viewing member and motorbike information, etc.
    }

    void listMotorbike()
    {
        int index = 1;
        std::cout << "All Available Motorbike Details:" << std::endl;
        for (const Motorbike &motorbike : motorbikes)
        {
            if (motorbike.getAvailability()) {
                motorbike.viewMotorbikeDetails(index);
            }
                index ++;
        }
    }

    void listMotorbikeDetails()
    {
        int index = 1;
        std::cout << "All Available Motorbike Details:" << std::endl;
        for (const Motorbike &motorbike : motorbikes)
        {
            if (motorbike.getAvailability()) {
                motorbike.viewMotorbikeDetailsWithReview(index);
            }
                index ++;
        }
    }

    void searchMotorbike(Member member)
    {
        int index = 1;
        std::string city;



        std::cout << "Please enter the city: ";
        std::getline(std::cin, city);

        std::cout << "All Available Motorbike Details in " << city << " that fit your credit points and rating score:" << std::endl;
        for (const Motorbike &motorbike : motorbikes)
        {
            if (motorbike.getLocation() == city 
                && (motorbike.getConsumingPoint() <= member.getCreditPoints())
                && (motorbike.getMinimumRenterRating() <= member.getRatingScores())
                && motorbike.getAvailability()
                )
            {
                motorbike.viewMotorbikeDetailsWithReview(index);
            }
                index++;
        }
    }

    void rentMotorbike(Member member)
{
    // Step 1: List available motorbikes
    searchMotorbike(member);

    // Step 2: Ask the user to choose a motorbike by index
    int motorbikeIndex;
    std::cout << "Enter the index of the motorbike you want to rent: ";
    std::cin >> motorbikeIndex;
    motorbikeIndex --;

    // Validate the user's input
    if (motorbikeIndex < 0 || motorbikeIndex >= motorbikes.size())
    {
        std::cout << "Invalid motorbike index. Please try again." << std::endl;
        return;
    }

    Motorbike &selectedMotorbike = motorbikes[motorbikeIndex];

    // Step 3: Display the maximum rental duration allowed
    int maxRentalDays = selectedMotorbike.getMaxRentalDays();
    std::cout << "Maximum rental duration allowed for this motorbike: " << maxRentalDays << " days" << std::endl;

    // Step 4: Ask the user for the rental period (start date and end date)
    DateTime startDate, endDate;
    std::cout << "Enter the start date (YYYY-MM-DD): ";
    std::string startDateStr;
    std::cin >> startDateStr;

    // Validate and parse the start date
    if (!DateTime::parseDateTime(startDateStr))
    {
        std::cout << "Invalid date format. Please use YYYY-MM-DD format." << std::endl;
        return;
    }

    std::cout << "Enter the end date (YYYY-MM-DD): ";
    std::string endDateStr;
    std::cin >> endDateStr;

    // Validate and parse the end date
    if (!DateTime::parseDateTime(endDateStr))
    {
        std::cout << "Invalid date format. Please use YYYY-MM-DD format." << std::endl;
        return;
    }

    startDate = DateTime::parseDateTime(startDateStr);
    endDate = DateTime::parseDateTime(endDateStr);

    // Step 5: Create a TimePeriod based on the start and end dates
    TimePeriod rentalPeriod(startDate, endDate);

    // Step 6: Calculate the total rental fee based on the rental period
    int totalFee = selectedMotorbike.calculateRentalFee(rentalPeriod);

    // Step 7: Check if the user can afford the rental
    if (currentAccount.getCreditPoints() < totalFee)
    {
        std::cout << "You do not have enough credit points to rent this motorbike." << std::endl;
        return;
    }

    // Step 8: Check if the user has a high enough rating
    if (currentAccount.getRatingScore() < selectedMotorbike.getMinimumRenterRating())
    {
        std::cout << "You do not have a high enough rating to rent this motorbike." << std::endl;
        return;
    }

    // Step 9: Check if the rental period is within the allowed maximum duration
    if (rentalPeriod.getNumberOfDays() > maxRentalDays)
    {
        std::cout << "The selected rental period exceeds the maximum allowed duration." << std::endl;
        return;
    }

    // Step 10: Send a rental request
    bool requestSent = currentAccount.requestToRentMotorbike(selectedMotorbike, rentalPeriod);

    if (requestSent)
    {
        std::cout << "Rental request sent successfully." << std::endl;
    }
}















};

int main()
{
    MotorbikeRentalApp app;
    app.run();
    return 0;
}
