#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <cstring>
#include "../include/hashpassword.h"


const uint32_t constants[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174
    };

// Simple SHA-256-like hash function (not for security purposes)
std::string HashPassword::get_SHA_256_SecurePassword(const std::string& passwordToHash, const std::string& salt) {
    // Concatenate password and salt
    std::string dataToHash = passwordToHash + salt;

    // Initialize hash result
    uint32_t hash[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    }; // Initial hash values (first 32 bits of the fractional parts of the square roots of the first 8 prime numbers)

    // Pre-processing (padding, length)
    uint64_t dataLength = dataToHash.length() * 8; // Length of the message in bits
    dataToHash += static_cast<char>(0x80); // Append a single '1' bit
    while (dataToHash.length() % 64 != 56) {
        dataToHash += static_cast<char>(0x00); // Pad with zeros to reach 448 bits (mod 512)
    }

    // Append the length of the message as a 64-bit big-endian integer
    for (int i = 7; i >= 0; --i) {
        dataToHash += static_cast<char>((dataLength >> (i * 8)) & 0xFF);
    }

    int numBlocks = dataToHash.size() / 64; // Calculate the number of 512-bit blocks
    for (int block = 0; block < numBlocks; ++block) {
        // Prepare message schedule
        uint32_t W[64] = {0}; // Message schedule

        // SHA-256 message schedule generation
        for (int t = 0; t < 16; ++t) {
            W[t] = (static_cast<uint32_t>(dataToHash[block * 64 + t * 4]) << 24) |
                   (static_cast<uint32_t>(dataToHash[block * 64 + t * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(dataToHash[block * 64 + t * 4 + 2]) << 8) |
                   static_cast<uint32_t>(dataToHash[block * 64 + t * 4 + 3]);
        }
        for (int t = 16; t < 64; ++t) {
            uint32_t s0 = (W[t - 15] >> 7 | W[t - 15] << 25) ^ (W[t - 15] >> 18 | W[t - 15] << 14) ^ (W[t - 15] >> 3);
            uint32_t s1 = (W[t - 2] >> 17 | W[t - 2] << 15) ^ (W[t - 2] >> 19 | W[t - 2] << 13) ^ (W[t - 2] >> 10);

            W[t] = W[t - 16] + s0 + W[t - 7] + s1;
        }

        // Initialize hash values for this block
        uint32_t a = hash[0];
        uint32_t b = hash[1];
        uint32_t c = hash[2];
        uint32_t d = hash[3];
        uint32_t e = hash[4];
        uint32_t f = hash[5];
        uint32_t g = hash[6];
        uint32_t h = hash[7];

        // Compression function
        for (int t = 0; t < 64; ++t) {
            uint32_t S1 = (e >> 6 | e << 26) ^ (e >> 11 | e << 21) ^ (e >> 25 | e << 7);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h + S1 + ch + constants[t] + W[t];
            uint32_t S0 = (a >> 2 | a << 30) ^ (a >> 13 | a << 19) ^ (a >> 22 | a << 10);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Update hash values for this block
        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
        hash[5] += f;
        hash[6] += g;
        hash[7] += h;
    }

    // Post-processing (hash result)
    std::ostringstream oss;
    for (int i = 0; i < 8; ++i) {
        oss << std::hex << std::setfill('0') << std::setw(8) << hash[i];
    }

    return oss.str();
}

// Simple salt generation function
std::string HashPassword::generateSalt() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int saltLength = 16; // Adjust the length as needed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, sizeof(charset) - 1);

    std::string salt;
    for (int i = 0; i < saltLength; ++i) {
        salt += charset[dist(gen)];
    }

    return salt;
}

