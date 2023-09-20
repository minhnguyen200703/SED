#ifndef METHOD_H
#define METHOD_H

#include <string>
#include <vector>

class Method {
public:
    static int readList(const std::string& fileName, const std::string& splitPoint);
    static std::string generateID(const std::string& id, const std::string& fileName, const std::string& splitPoint);
    static std::string validateEmpty(std::string variable);
    static std::string validatePhone(std::string phoneNumber);
    static std::string validateEmail(std::string email);
    static int validatePrice(std::string priceInput);
    static int validateNumber(std::string str);
    static void removeById(const std::string& id, const std::string& fileName, const std::string& split);
    static void removeByName(const std::string& name, const std::string& fileName, const std::string& split);
    static double validateDouble(const std::string& str);
};

#endif  // METHOD_H
