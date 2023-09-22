#include "../include/hashpassword.h"
#include <iostream>
#include <cryptopp880/sha.h>
#include <cryptopp880/hex.h>
#include <cryptopp880/osrng.h>

std::string HashPassword::get_SHA_256_SecurePassword(const std::string& passwordToHash, const std::string& salt) {
    CryptoPP::SHA256 hash;
    std::string generatedPassword;

    CryptoPP::StringSource s(passwordToHash + salt, true,
        new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(generatedPassword))));

    return generatedPassword;
}

std::string HashPassword::getSalt() {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::byte salt[16];
    rng.GenerateBlock(salt, sizeof(salt));

    std::string saltStr(reinterpret_cast<const char*>(salt), sizeof(salt));

    return saltStr;
}
