#include "Account.h"
#include "Admin.h" // You'll need to create Admin and Customer classes
#include "member.h" // You'll need to create Admin and Customer classes

Account::Account(std::string id, std::string usernameReg, std::string password) {
    this->id = id;
    this->username = usernameReg;
    this->salt = HashPassword::getSalt(); // Implement HashPassword class
    this->password = HashPassword::get_SHA_256_SecurePassword(password, this->salt);
}

Account::Account(std::string id, std::string usernameReg, std::string password, std::string salt) {
    this->id = id;
    this->username = usernameReg;
    this->salt = salt;
    this->password = HashPassword::get_SHA_256_SecurePassword(password, this->salt);
}

Account::Account(std::string id, std::string usernameReg) {
    this->id = id;
    this->username = usernameReg;
}

std::string Account::getId() const {
    return id;
}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getSalt() const {
    return salt;
}

void Account::setSalt(std::string salt) {
    this->salt = salt;
}

bool Account::checkPassword(std::string password) const {
    std::string hashedPassword = HashPassword::get_SHA_256_SecurePassword(password, this->salt);
    return this->password == hashedPassword;
}

std::string Account::getPassword() const {
    return password;
}

// bool Account::login(const std::string& fileName, const std::string& username, const std::string& password) {
//     Account* account = nullptr;

//     // Check if admin
//     // Implement this part to read and compare admin credentials

//     // Check if user
//     // Implement this part to read and compare user credentials

//     return account;
// }


// Account* Account::login(const std::string& fileName, const std::string& username, const std::string& password) {
//     Account* account = nullptr;

//     // Check if admin
//     std::ifstream adminFile(".\\data\\admin.txt");
//     if (adminFile.is_open()) {
//         std::string adminLine;
//         std::getline(adminFile, adminLine);
//         adminFile.close();

//         // Split the admin account data by '|'
//         std::istringstream adminStream(adminLine);
//         std::string adminData[3];
//         for (int i = 0; i < 3; ++i) {
//             std::getline(adminStream, adminData[i], '|');
//         }

//         if (username == adminData[1] && password == adminData[2]) {
//             // Successfully logged in as admin
//             account = new Admin(adminData[0], adminData[1], adminData[2]);
//             return account;
//         }
//     }

//     // Check if user
//     try {
//         std::ifstream userFile(fileName);
//         if (userFile.is_open()) {
//             std::string line;
//             while (std::getline(userFile, line)) {
//                 // Split the user account data by '|'
//                 std::istringstream userStream(line);
//                 std::string userData[9];
//                 for (int i = 0; i < 9; ++i) {
//                     std::getline(userStream, userData[i], '|');
//                 }

//                 std::string salt = userData[8];
//                 std::string hashedPasswordX = HashPassword::get_SHA_256_SecurePassword(password, salt);

//                 if (username == userData[1] && hashedPasswordX == userData[2]) {
//                     // Successfully logged in as a user
//                     account = new Member(userData[0], userData[1], userData[2], userData[3], userData[4], userData[5], userData[6], userData[7], userData[8]);
//                     userFile.close();
//                     return account;
//                 }
//             }
//             userFile.close();
//         } else {
//             std::cerr << "Error reading from user database file." << std::endl;
//         }

//         if (!account) {
//             std::cout << "Invalid username or password." << std::endl;
//         }
//     } catch (const std::exception& e) {
//         std::cerr << "Error reading from database file: " << e.what() << std::endl;
//     }

//     return account;
// }
