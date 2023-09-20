#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <ctime>
#include <cstdlib>

using namespace std;
class Method {
public:
    static int readList(const string& fileName, const string& splitPoint) {
        ifstream file(fileName);
        string line;
        string lastLine = "";

        while (getline(file, line)) {
            lastLine = line;
        }
        file.close();

        if (lastLine.empty()) {
            return 0;
        } else {
            string id = lastLine.substr(0, lastLine.find(splitPoint));
            return stoi(id.substr(1));
        }
    }

    static string generateID(const string& id, const string& fileName, const string& splitPoint) {
        int amount = readList(fileName, splitPoint);
        if (amount <= 0) {
            return id + "1";
        } else {
            amount++;
            return id + to_string(amount);
        }
    }

    static string validateEmpty(string variable) {
        do {
            if (variable.empty() || variable.find_first_not_of(' ') == string::npos) {
                cout << "Your full name is invalid, please re-input your full name: ";
                getline(cin, variable);
            } else {
                break;
            }
        } while (true);
        return variable;
    }

    static string validatePhone(string phoneNumber) {
        do {
            if (phoneNumber.empty() || !regex_match(phoneNumber, regex("^(0|\\+84)(\\s|\\.)?((3[2-9])|(5[689])|(7[06-9])|(8[1-689])|(9[0-46-9]))(\\d)(\\s|\\.)?(\\d{3})(\\s|\\.)?(\\d{3})$"))) {
                cout << "Your phone number is invalid, please re-input your phone number: ";
                getline(cin, phoneNumber);
            } else {
                break;
            }
        } while (true);
        return phoneNumber;
    }

    static string validateEmail(string email) {
        do {
            if (email.empty() || !regex_match(email, regex("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$"))) {
                cout << "Your email is invalid, please re-input your email: ";
                getline(cin, email);
            } else {
                break;
            }
        } while (true);
        return email;
    }

    static int validatePrice(string priceInput) {
        int price = 0;
        bool valid = false;
        while (!valid) {
            try {
                price = stoi(priceInput);
                if (price < 0) {
                    cout << "The product price cannot be less than 0, please re-input the price: ";
                } else if (price > 2000000000) {
                    cout << "The product price cannot be more than 2 billions, please re-input the price: ";
                } else {
                    valid = true;
                }
            } catch (invalid_argument& e) {
                cout << "Invalid input. Please enter a valid positive number: ";
            }
            if (!valid) {
                getline(cin, priceInput);
            }
        }
        return price;
    }

    static int validateNumber(string str) {
        int number = 0;
        bool valid = false;
        while (!valid) {
            try {
                number = stoi(str);
                if (number < 0) {
                    cout << "The product price cannot be less than 0, please re-input the price: ";
                } else {
                    valid = true;
                }
            } catch (invalid_argument& e) {
                cout << "Invalid input. Please enter a valid positive number: ";
            }
            if (!valid) {
                getline(cin, str);
            }
        }
        return number;
    }

    static double validateDouble(const std::string& str) {
    double number = 0.0;
    bool valid = false;

    std::string input = str; // Create a new string to store user input

    while (!valid) {
        try {
            number = std::stod(input);
            if (number < 0.0) {
                std::cout << "Invalid input. Please enter a non-negative number: ";
            } else {
                valid = true;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a valid number: ";
        } catch (const std::out_of_range& e) {
            std::cout << "Input out of range. Please enter a smaller number: ";
        }

        if (!valid) {
            std::getline(std::cin, input);
            // Validate that input is not empty to avoid an infinite loop
            if (input.empty()) {
                std::cout << "Invalid input. Please enter a valid number: ";
            }
        }
    }
    return number;
}


    static void removeById(const string& id, const string& fileName, const string& split) {
        ifstream inputFile(fileName);
        ofstream outputFile("temp.txt");
        string line;

        while (getline(inputFile, line)) {
            string currentId = line.substr(0, line.find(split));
            if (currentId != id) {
                outputFile << line << endl;
            }
        }

        inputFile.close();
        outputFile.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());
    }

    static void removeByName(const string& name, const string& fileName, const string& split) {
        ifstream inputFile(fileName);
        ofstream outputFile("temp.txt");
        string line;

        while (getline(inputFile, line)) {
            string currentName = line.substr(line.find(split) + 1);
            if (currentName != name) {
                outputFile << line << endl;
            }
        }

        inputFile.close();
        outputFile.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());
    }
};