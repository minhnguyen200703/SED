#ifndef HASHPASSWORD_H
#define HASHPASSWORD_H

#include <string>

class HashPassword {
public:
    static std::string get_SHA_256_SecurePassword(const std::string& passwordToHash, const std::string& salt);
    static std::string getSalt();
};

#endif
