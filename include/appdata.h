#ifndef APPDATA_H
#define APPDATA_H

#include <string>
#include <vector>
#include "Member.h"
#include "Motorbike.h"

class AppData {
private:
    std::vector<Member> members;
    std::vector<Motorbike> motorbikes;

    std::string dataFileName;

public:
    AppData(std::string fileName);

    // Load data from a file into the application
    bool loadDataFromFile();

    // Save data from the application to a file
    bool saveDataToFile();

    // Add a member to the data
    void addMember(const Member& member);

    // Add a motorbike to the data
    void addMotorbike(const Motorbike& motorbike);

    // Get a list of all members
    std::vector<Member> getAllMembers() const;

    // Get a list of all motorbikes
    std::vector<Motorbike> getAllMotorbikes() const;
};

#endif
