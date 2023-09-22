// AppData.cpp
#include "../include/appdata.h"
#include <fstream>
#include <iostream>

AppData::AppData(std::string fileName) : dataFileName(fileName) {
    // Initialize other AppData attributes or perform necessary setup
}

bool AppData::loadDataFromFile() {
    // Implement loading data from a file into the application
    // You should read data from the dataFileName and populate the members and motorbikes vectors.
    // Return true if loading is successful, otherwise return false.

    // Example: Read member data from a file
    std::ifstream inputFile(dataFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Failed to open data file." << std::endl;
        return false;
    }

    // Read and populate members vector
    // ...

    // Read and populate motorbikes vector
    // ...

    inputFile.close();
    return true;
}

bool AppData::saveDataToFile() {
    // Implement saving data from the application to a file
    // You should write data from the members and motorbikes vectors to the dataFileName.
    // Return true if saving is successful, otherwise return false.

    // Example: Write member data to a file
    std::ofstream outputFile(dataFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Failed to open data file." << std::endl;
        return false;
    }

    // Write members vector data
    // ...

    // Write motorbikes vector data
    // ...

    outputFile.close();
    return true;
}

void AppData::addMember(const Member& member) {
    // Implement adding a member to the data
    // Add the provided member to the members vector.
}

void AppData::addMotorbike(const Motorbike& motorbike) {
    // Implement adding a motorbike to the data
    // Add the provided motorbike to the motorbikes vector.
}

std::vector<Member> AppData::getAllMembers() const {
    // Implement getting a list of all members
    // Return the members vector.
    return members;
}

std::vector<Motorbike> AppData::getAllMotorbikes() const {
    // Implement getting a list of all motorbikes
    // Return the motorbikes vector.
    return motorbikes;
}
