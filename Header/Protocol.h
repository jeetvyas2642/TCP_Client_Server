#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "Buffer.h"
#include <string>
#include <vector>

class Protocol {
public:
    // Serialize a message into a vector of characters
    static std::vector<char> SerializeMessage(const std::string& message);

    // Deserialize a message from a buffer
    static std::string DeserializeMessage(Buffer& buffer);
};

#endif // PROTOCOL_H
