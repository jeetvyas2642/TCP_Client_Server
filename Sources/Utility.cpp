#include "Utility.h"
#include <sstream>
#include <WinSock2.h> // Include any necessary headers here

// Function to convert a 32-bit value to big endian
uint32_t Utility::ConvertToBigEndian(uint32_t value) {
    return htonl(value); // Use htonl to convert to big endian
}

// Function to convert a 32-bit value to little endian
uint32_t Utility::ConvertToLittleEndian(uint32_t value) {
    return ntohl(value); // Use ntohl to convert to little endian
}

// Function to split a string into a vector of substrings based on a delimiter
std::vector<std::string> Utility::SplitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}
