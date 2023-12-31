#include "../include/account.h"       // Include your member class header file
#include "../include/member.h"        // Include your member class header file
#include "../include/motorbike.h"     // Include your motorbike class header file
#include "../include/admin.h"         // Include your admin class header file
#include "../include/rentalRequest.h" // Include your Location class header file
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream> // Include the <sstream> header

using namespace std;

class Member;
class Motorbike;
class Account;
class Admin;
class DateTime;
class NonMember;
class RentalRequest;
class Review;
class TimePeriod;

class MotorbikeRentalApp
{
private:
    vector<Member> members;         // Vector to store member objects
    vector<Motorbike *> motorbikes; // Vector to store motorbike objects
    vector<RentalRequest> rentalRequests;
    Member *currentMember;
    // Vector to store motorbike objects

public:
    MotorbikeRentalApp()
    {
        loadData();
    }

    void run()
    {
        int choice;
        do
        {
            std::cout << "Request" << std::endl;
            std::cout << rentalRequests.size() << std::endl;

            for (const RentalRequest rentalRequest : rentalRequests)
            {
                rentalRequest.displayRequestDetails();
            };

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

    void displayWelcomeScreen()
    {
        // Display welcome screen with options for guest, member, and admin
        cout << "EEET2482/COSC2082 ASSIGNMENT" << endl;
        cout << "MOTORBIKE RENTAL APPLICATION" << endl
             << endl;
        cout << "Instructor: Dr. Ling Huo Chong" << endl;
        cout << "Group: Group No." << endl;
        cout << "s3932112, Nguyen Nhat Minh" << endl;
        cout << "s3924942, Luu Quoc Nhat " << endl;
        cout << "s3922086, Luong Thao My" << endl;
        cout << "s3927502, Vu Tuan Linh" << endl
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
                registerMember();
                std::cout << "Registration successful. Going back to main menu..." << std::endl;
                registered = true;
                break;
            }
            case 2:
            {
                listMotorbikes();
                break;
            }
            case 3:
            {
                // Exit the guest menu
                saveData();
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

        std::cout << "Please enter your username: ";
        std::cin >> username;

        std::cout << "Please enter your password: ";
        std::cin >> password;

        for (Member &member : members)
        {
            if (member.getUsername() == username && member.getPassword() == password)
            {
                currentMember = &member; // Store a pointer to the logged-in member
                isLogged = true;
                std::cout << "Login successful. Welcome, " << member.getFullName() << "!" << std::endl;
                member.editMemberRatingScore();
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
        bool i = true;
        do
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
            std::cout << "10. Rate Renters\n";
            std::cout << "11. View all motorbikes\n";
            std::cout << "12. Add credit points\n";
            std::cout << "0. Logout\n";
            std::cout << "Enter your choice: " << std::endl;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                // View information
                std::cout << " Hi";

                currentMember->viewMemberInfo();
                break;

            case 2:
                currentMember->listMotorbike();
                addMembersMotorbikesToMotorbikesVector();
                break;
            case 3:
                // Unlist motorbike
                currentMember->unlistMotorbike();
                addMembersMotorbikesToMotorbikesVector();
                break;
            case 4:
                // Search Motorbike
                searchMotorbike(currentMember);
                break;
            case 5:
                // Request to rent motorbike
                rentMotorbike(currentMember);
                break;
            case 6:
                currentMember->Member::viewRequests("1"); // View all imcoming rental requests
                break;
            case 7:
                currentMember->Member::viewRequests("2"); // View my requests
                break;
            case 8:
                viewAndAcceptRentalRequest(currentMember);
                // You can prompt the member to confirm the rental.
                break;
            case 9:
                // Implement rating a rented motorbike
                currentMember->Member::RentRequestedMotorbike();
                break;
            case 10:
                currentMember->Member::RateRenter();
                break;
            case 11:
                listMotorbikes();

                break;

            case 12:
                currentMember->Member::addCreditPoints();

                break;
            case 0:
                std::cout << "Logging out..." << std::endl;
                i = false;
                std::cout << "Logging out...1" << std::endl;
                saveData();
                std::cout << "Logging out...2" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (i);
    }

    void handleAdminMenu()
    {
        // Admin login (you can keep this part as it is)
        std::string username, password;
        bool isLogged = false;

        std::cout << "Please enter your username: ";
        std::cin >> username;

        std::cout << "Please enter your password: ";
        std::cin >> password;

        if (username == "admin" && password == "admin")
        {
            isLogged = true;
            std::cout << "Login successful. Welcome admin!" << std::endl;
        }
        else
        {
            std::cout << "Login failed. Please check your username and password." << std::endl;
        }

        if (!isLogged)
        {
            std::cout << "Returning to menu...." << std::endl;
            return;
        }

        int choice;
        bool j = true;
        while (j)
        {
            std::cout << "\nAdmin Menu\n";
            std::cout << "1. View All Member's Information\n";
            std::cout << "2. View All Motorbike's Information\n";
            std::cout << "0. Logout\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                // View all member's information
                viewAllMemberInformation();
                break;
            case 2:
                // View all motorbike's information
                viewAllMotorbikeInformation();
                break;
            case 0:
                std::cout << "Logging out..." << std::endl;
                j = false;
                saveData();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }

    void listMotorbikes()
    {
        int index = 1;
        std::cout << "All Available Motorbike Details:" << std::endl;
        for (const Motorbike *motorbike : motorbikes)
        {
            motorbike->Motorbike::viewMotorbikeDetails(index);

            if (motorbike->Motorbike::getAvailability())
            {
                motorbike->Motorbike::viewMotorbikeDetails(index);
            }
            index++;
        }
    }

    void listMotorbikeDetails()
    {
        int index = 1;
        std::cout << "All Available Motorbike Details:" << std::endl;
        for (const Motorbike *motorbike : motorbikes)
        {
            if (motorbike->Motorbike::getAvailability())
            {
                motorbike->Motorbike::viewMotorbikeDetailsWithReview(index);
            }
            index++;
        }
    }

    void searchMotorbike(Member *member)
    {
        int index = 1;
        std::string city;
        if (motorbikes.size() == 0)
        {
            std::cout << "There is no Motorbike at the moment! " << std::endl;
        }
        else
        {

            std::cout << "Please enter the city: ";
            std::cin.ignore();
            std::getline(std::cin, city);

            std::cout << "All Available Motorbike Details in " << city << " that fit your credit points and rating score:" << std::endl;
            for (const Motorbike *motorbike : motorbikes)
            {
                if (motorbike->Motorbike::getLocation() == city && (motorbike->Motorbike::getConsumingPoint() <= member->Member::getCreditPoints()) && (motorbike->Motorbike::getMinimumRenterRating() <= member->Member::getRatingScores()) && motorbike->Motorbike::getAvailability())
                {
                    motorbike->Motorbike::viewMotorbikeDetailsWithReview(index);
                }
                index++;
            }
        }
    }

    void rentMotorbike(Member *member)
    {
        // Step 1: List available motorbikes
        searchMotorbike(member);

        // Step 2: Ask the user to choose a motorbike by index
        int motorbikeIndex;
        std::cout << "Enter the index of the motorbike you want to rent: ";
        std::cin >> motorbikeIndex;
        motorbikeIndex--;

        // Validate the user's input
        if (motorbikeIndex < 0 || motorbikeIndex >= motorbikes.size())
        {
            std::cout << "Invalid motorbike index. Please try again." << std::endl;
            return;
        }

        Motorbike *selectedMotorbike = motorbikes[motorbikeIndex];

        // Step 3: Display the maximum rental duration allowed
        int maxRentalDays = div(member->Member::getCreditPoints(), selectedMotorbike->Motorbike::getConsumingPoint()).quot;

        std::cout << "Maximum rental duration allowed for this motorbike: " << maxRentalDays << " days" << std::endl;

        // Step 4: Ask the user for the rental period (start date and end date)
        DateTime startDate, endDate;
        std::cout << "Enter the start date (YYYY-MM-DD): ";
        std::string startDateStr;
        std::cin >> startDateStr;

        // Validate and parse the start date
        if (!startDate.DateTime::parseDateTime(startDateStr))
        {
            std::cout << "Invalid date format. Please use YYYY-MM-DD format." << std::endl;
            return;
        }

        std::cout << "Enter the end date (YYYY-MM-DD): ";
        std::string endDateStr;
        std::cin >> endDateStr;

        // Validate and parse the end date
        if (!endDate.DateTime::parseDateTime(endDateStr))
        {
            std::cout << "Invalid date format. Please use YYYY-MM-DD format." << std::endl;
            return;
        }

        // Step 5: Create a TimePeriod based on the start and end dates
        TimePeriod rentalPeriod(startDate, endDate);

        // Step 6: Check if the motorbike is available for the specified rental period

        if (!selectedMotorbike->isAvailable() || !selectedMotorbike->periodIsValid(rentalPeriod))
        {
            rentalPeriod.printPeriod();

            std::cout << "Motorbike is not available for the specified rental period or the period is invalid." << std::endl;
            return;
        }

        // Step 7: Calculate the total rental fee based on the rental period
        int totalFee = selectedMotorbike->getConsumingPoint() * rentalPeriod.getNumberOfDays();

        // Step 8: Check if the user can afford the rental
        if (member->getCreditPoints() < totalFee)
        {
            std::cout << "You do not have enough credit points to rent this motorbike." << std::endl;
            return;
        }

        // Step 9: Check if the user has a high enough rating
        if (member->getRatingScores() < selectedMotorbike->getMinimumRenterRating())
        {
            std::cout << "You do not have a high enough rating to rent this motorbike." << std::endl;
            return;
        }

        // Step 10: Send a rental request
        bool requestSent = member->requestToRentMotorbike(selectedMotorbike, rentalPeriod);

        if (requestSent)
        {
            std::cout << "Rental request sent successfully." << std::endl;
        }
        else
        {
            std::cout << "An error has occured." << std::endl;
        }
    }

    void viewAndAcceptRentalRequest(Member *currentMember)
    {

        std::cout << "List of pending Rental Requests:" << std::endl;

        // Display the list of rental requests with indices
        currentMember->viewRentalRequests("1", "Pending");

        // Prompt the user to select a rental request
        std::cout << "Enter the index of the rental request you want to accept: ";
        int selectedIndex;
        std::cin >> selectedIndex;

        // Check if the selected index is valid
        if (selectedIndex >= 1 && selectedIndex <= static_cast<int>(currentMember->getRentalRequests().size()))
        {
            // Display the details of the selected rental request
            currentMember->getRentalRequests()[selectedIndex - 1].displayRequestDetails(); // You should implement this function in RentalRequest class
            std::cout << "Do you really want to accept this request?\n All other request that overlap on this request will be deleted! (Y/N)" << std::endl;
            std::string choice;
            std::cin >> choice;
            if (choice == "Y")
            {
                currentMember->setRentalRequests(currentMember->acceptRequest(&currentMember->getRentalRequests()[selectedIndex - 1]));
                std::cout << "Request accepted. All other overlapped requests have been denied!" << std::endl;
            }
            else
            {
                std::cout << "Returning to main menu..." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid selection. Please enter a valid index." << std::endl;
        }
    }

    void loadData()
    {
        // Load data from the member.txt file into the members vector
        ifstream memberFile("./data/member.txt");
        if (memberFile.is_open())
        {
            string line;
            while (getline(memberFile, line))
            {
                // Split the line into fields
                vector<string> fields;
                string field;
                istringstream lineStream(line);
                while (getline(lineStream, field, '|'))
                {
                    fields.push_back(field);
                }

                if (fields.size() == 13)
                {
                    // Assuming your Member class has a constructor that takes these fields as parameters
                    Member member(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5], fields[6], fields[7],
                                  fields[8], fields[9], fields[10], stoi(fields[11]), stod(fields[12]));
                    members.push_back(member);
                }
                else
                {
                    cerr << "Invalid data in member.txt: " << line << endl;
                }
            }
            memberFile.close();
        }
        else
        {
            cerr << "Error opening member.txt" << endl;
        }

        // Load data from the motorbike.txt file into the motorbikes vector
        ifstream motorbikeFile("./data/motorbike.txt");
        if (motorbikeFile.is_open())
        {
            string line;
            while (getline(motorbikeFile, line))
            {
                // Split the line into fields
                vector<string> fields;
                string field;
                istringstream lineStream(line);
                while (getline(lineStream, field, '|'))
                {

                    fields.push_back(field);
                }

                if (fields.size() == 12)
                {

                    Member *foundMember = nullptr;
                    for (Member &member : members)
                    {
                        if (member.getId() == fields[0])
                        {
                            foundMember = &member;
                            break;
                        }
                    };

                    // Parse and add time periods
                    vector<TimePeriod> timePeriods;
                    istringstream timePeriodStream(fields[9]);
                    string timePeriod;
                    while (getline(timePeriodStream, timePeriod, ';'))
                    {
                        vector<string> dateParts;
                        istringstream dateStream(timePeriod);
                        string datePart;
                        vector<int> dateValues;
                        while (getline(dateStream, datePart, ','))
                        {
                            dateValues.push_back(stoi(datePart));
                        }
                        if (dateValues.size() == 6)
                        {
                            DateTime startDate(dateValues[0], dateValues[1], dateValues[2]);
                            DateTime endDate(dateValues[3], dateValues[4], dateValues[5]);
                            TimePeriod period(startDate, endDate);
                            timePeriods.push_back(period);
                        }
                    }
                    Motorbike motorbike(fields[1], fields[2], stod(fields[3]), fields[4], stoi(fields[5]),
                                        fields[6], stoi(fields[11]), timePeriods, stoi(fields[10]), foundMember, stod(fields[7]));
                    foundMember->setMotorbike(motorbike);

                    motorbikes.push_back(&motorbike);
                }
                else if (fields.size() == 9)
                {

                    Member *foundMember = nullptr;
                    for (Member &member : members)
                    {
                        if (member.getId() == fields[0])
                        {
                            foundMember = &member;
                            break;
                        }
                    };

                    Motorbike *motorbike = new Motorbike(fields[1], fields[2], stod(fields[3]), fields[4], stoi(fields[5]),
                                                         fields[6], foundMember, stod(fields[7]));
                    foundMember->setMotorbike(*motorbike);
                    motorbikes.push_back(motorbike);
                }
                else
                {
                    cerr << "Invalid data in motorbike.txt: " << line << endl;
                }
            }
            motorbikeFile.close();
        }
        else
        {
            cerr << "Error opening motorbike.txt" << endl;
        }

        // Load data from the rentalrequests.txt file into the rentalRequests vector
        ifstream rentalRequestsFile("./data/rentalrequest.txt");
        if (rentalRequestsFile.is_open())
        {
            std::cout << "test1" << std::endl;
            string line;
            while (getline(rentalRequestsFile, line))
            {
                std::cout << "rentalRequestsFile" << std::endl;

                // Split the line into fields
                vector<string> fields;
                string field;
                istringstream lineStream(line);
                while (getline(lineStream, field, '|'))
                {
                    std::cout << field << std::endl;

                    fields.push_back(field);
                }

                if (fields.size() == 9)
                {

                    Member renter;
                    Member owner;
                    for (auto &member : members)
                    {
                        if (member.getId() == fields[1])
                        {
                            renter = member;
                        }
                        if (member.getId() == fields[2])
                        {
                            owner = member;
                        }
                    };
                    // Assuming your RentalRequest class has a constructor that takes these fields as parameters

                    vector<string> dateParts;
                    istringstream dateStream(fields[3]);
                    string datePart;
                    vector<int> dateValues;
                    TimePeriod period;
                    while (getline(dateStream, datePart, ','))
                    {
                        dateValues.push_back(stoi(datePart));
                    }

                    if (dateValues.size() == 6)
                    {
                        DateTime startDate(dateValues[2], dateValues[1], dateValues[0]);
                        DateTime endDate(dateValues[5], dateValues[4], dateValues[3]);
                        period = TimePeriod(startDate, endDate); // Assign the TimePeriod object
                    }
                    Review motorbikeReview = Review(stoi(fields[4]), fields[5]);
                    Review renterReview = Review(stoi(fields[6]), fields[7]);

                    RentalRequest request(fields[0], renter, owner.getMotorbike(), period, motorbikeReview, renterReview, fields[8]);

                    request.displayRequestDetails();

                    rentalRequests.push_back(request);
                    renter.addRentalRequest(request);
                    renter.editMemberRatingScore();
                    owner.addRentedRentalRequest(request);
                    owner.getMotorbike()->editMotorbikeRatingScore();
                }
                else
                {
                    cerr << "Invalid data in rentalrequests.txt: " << line << endl;
                }
            }
            rentalRequestsFile.close();
        }
        else
        {
            cerr << "Error opening rentalrequests.txt" << endl;
        }
        addMembersMotorbikesToMotorbikesVector();
        // getAllRequests();
    }

    void writeMembersToFile(const std::string &filename)
    {
        std::ofstream file(filename, std::ios::trunc);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        for (const Member &member : members)
        {
            file << member.Member::getId() << "|"
                 << member.Member::getUsername() << "|"
                 << member.Member::getPassword() << "|"
                 << member.Member::getSalt() << "|"
                 << member.Member::getFullName() << "|"
                 << member.Member::getPhoneNumber() << "|"
                 << member.Member::getIdType() << "|"
                 << member.Member::getIdNumber() << "|"
                 << member.Member::getDriverLicenseNumber() << "|"
                 << member.Member::getExpiryDate() << "|"
                 << member.Member::getCity() << "|"
                 << member.Member::getCreditPoints() << "|"
                 << member.Member::getRatingScores() << "\n";
        }

        file.close();
    }

    void writeMotorbikesToFile(const std::string &filename)
    {
        std::ofstream file(filename, std::ios::trunc);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        for (const Motorbike *motorbike : motorbikes)
        {
            file << motorbike->getOwner()->getId() << "|"
                 << motorbike->getModel() << "|"
                 << motorbike->getColor() << "|"
                 << motorbike->getEngineSize() << "|"
                 << motorbike->getTransmissionMode() << "|"
                 << motorbike->getYearMade() << "|"
                 << motorbike->getDescription() << "|"
                 << motorbike->getRatingScores() << "|";

            if (motorbike->getAvailability())
            {
                file << "true|";
                const std::vector<TimePeriod> &timePeriods = motorbike->getAvailablePeriods();
                for (const TimePeriod &period : timePeriods)
                {
                    file << period.getStartDate().getDay() << ","
                         << period.getStartDate().getMonth() << ","
                         << period.getStartDate().getYear() << ","
                         << period.getEndDate().getDay() << ","
                         << period.getEndDate().getMonth() << ","
                         << period.getEndDate().getYear();
                    if (&period != &timePeriods.back())
                    {
                        file << ";";
                    }
                }
                file << "|" << motorbike->getMinimumRenterRating() << "|"
                     << motorbike->getConsumingPoint() << "\n";
            }
            else
            {
                file << "false"
                     << "\n";
            }
        }

        file.close();
    }

    void writeRentalRequestsToFile(const std::string &filename)
    {
        std::ofstream file(filename, std::ios::trunc);
        std::cout << "Hi1" << std::endl;

        if (!file.is_open())
        {
            std::cout << "Hi2" << std::endl;
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        for (const RentalRequest &request : rentalRequests)

        {
            std::cout << "Hi33" << std::endl;

            file << request.getId() << "|"
                 << request.getRequester().getId() << "|"
                 << request.getMotorbike().getOwner()->getId() << "|"
                 << request.getRentalPeriod().getStartDate().getDay() << ","
                 << request.getRentalPeriod().getStartDate().getMonth() << ","
                 << request.getRentalPeriod().getStartDate().getYear() << ","
                 << request.getRentalPeriod().getEndDate().getDay() << ","
                 << request.getRentalPeriod().getEndDate().getMonth() << ","
                 << request.getRentalPeriod().getEndDate().getYear() << "|"
                 << request.getMotorbikeReview().getScore() << "|"
                 << request.getMotorbikeReview().getComment() << "|"
                 << request.getRenterReview().getScore() << "|"
                 << request.getRenterReview().getComment() << "|"
                 << request.getStatus() << "\n";
        }

        file.close();
    }

    void saveData()
    {
        // getAllRequests();
        writeMembersToFile("./data/member.txt");
        std::cout << "./data/member.txt" << std::endl;

        writeMotorbikesToFile("./data/motorbike.txt");
        std::cout << "./data/motorbike.txt" << std::endl;

        writeRentalRequestsToFile("./data/rentalrequest.txt");
        std::cout << "./data/rentalrequest.txt" << std::endl;

        std::cout << "File saved!" << std::endl;
    }

    void viewAllMemberInformation()
    {
        std::cout << "All Member Information:" << std::endl;
        for (Member &member : members)
        {
            member.viewMemberInfo();
            std::cout << std::endl;
        }
    }

    void viewAllMotorbikeInformation()
    {
        std::cout << "All Motorbike Information:" << std::endl;
        int index = 1;
        for (const Motorbike *motorbike : motorbikes)
        {
            motorbike->viewMotorbikeDetailsWithReview(index);
            std::cout << std::endl;
            index++;
        }
    }

    void registerMember()
    {
        // You should prompt the user to enter necessary information and store it securely.
        std::string username, password, fullName, phoneNumber, idType, idNumber, driverLicenseNumber, expiryDate, city;

        // Check if the entered username already exists
        bool usernameExists = false;
        do
        {
            std::cout << "Enter Username: ";
            std::cin >> username;
            usernameExists = false;

            // Loop through existing members to check if the username exists
            for (const Member &existingMember : members)
            {
                if (existingMember.Account::getUsername() == username)
                {
                    std::cout << "Username already exists. Please choose a different username." << std::endl;
                    usernameExists = true;
                    break;
                }
            }
        } while (usernameExists);

        std::cout << "Enter Password: ";
        std::cin >> password; // You can use a password validation function here.

        std::cout << "Enter Full Name: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, fullName);
        std::cout << "Enter Phone Number: " << std::endl;
        std::cin >> phoneNumber;
        std::cout << "Enter ID Type (Passport/CitizenID): " << std::endl;
        std::cin >> idType;
        std::cout << "Enter ID Number: " << std::endl;
        std::cin >> idNumber;
        std::cout << "Enter Driver License Number: " << std::endl;
        std::cin >> driverLicenseNumber;
        std::cout << "Enter Expiry Date: " << std::endl;
        std::cin >> expiryDate;
        std::cout << "Enter City: " << std::endl;
        std::cin >> city;

        // Create a Member object with the provided information
        Member newMember(username, password, fullName, phoneNumber, idType, idNumber, driverLicenseNumber, expiryDate, city);

        // Store the member data or perform any necessary operations
        members.push_back(newMember);

        std::cout << "Member registration completed. You have 20 credit points" << std::endl;
        std::cout << "Adding motorbike..." << std::endl;
        newMember.addMotorbike();
        Motorbike *newMotorbike = newMember.getMotorbike();

        motorbikes.push_back(newMotorbike);
        saveData();
    }

    void addMembersMotorbikesToMotorbikesVector()
    {
        motorbikes.clear();
        for (Member &member : members)
        {
            Motorbike *motorbike = member.getMotorbike();
            if (motorbike)
            {
                motorbikes.push_back(motorbike);
            }
        }
    }

    // void getAllRequests()
    // {
    //     rentalRequests.clear();

    //     for (const Member &member : members)
    //     {
    //         // Loop through the rental requests of the current member
    //         for (const RentalRequest &request : member.getRentalRequests())
    //         {
    //             rentalRequests.push_back(request);
    //         }

    //         // Loop through the rentedRentalRequests of the current member
    //         for (const RentalRequest &request : member.getRentedRentalRequests())
    //         {
    //             // Check if the request's ID is not already in rentalRequests
    //             bool isDuplicate = false;
    //             for (const RentalRequest &existingRequest : rentalRequests)
    //             {
    //                 if (request.getId() == existingRequest.getId())
    //                 {
    //                     isDuplicate = true;
    //                     break;
    //                 }
    //             }

    //             // If it's not a duplicate, add it to rentalRequests
    //             if (!isDuplicate)
    //             {
    //                 rentalRequests.push_back(request);
    //             }
    //         }
    //     }
    // }
};

int main()
{
    MotorbikeRentalApp app;
    app.run();

    return 0;
}
