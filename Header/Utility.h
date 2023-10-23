#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <cstdint> // Include the required header for uint32_t

class Utility {
public:
    // Convert an unsigned 32-bit integer to big endian format
    static uint32_t ConvertToBigEndian(uint32_t value);

    // Convert an unsigned 32-bit integer to little endian format
    static uint32_t ConvertToLittleEndian(uint32_t value);

    // Split a string into a vector of substrings using a delimiter character
    static std::vector<std::string> SplitString(const std::string& str, char delimiter);
};

#endif // UTILITY_H
