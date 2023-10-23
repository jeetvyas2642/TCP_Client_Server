#include "Protocol.h"
#include <algorithm>
#include <WinSock2.h>

// Serialize a message into a vector of characters
std::vector<char> Protocol::SerializeMessage(const std::string& message) {
    // Calculate the message length and convert it to big-endian
    uint32_t messageLength = static_cast<uint32_t>(message.size());
    uint32_t messageLengthBE = htonl(messageLength);

    // Create a Buffer with the default size
    Buffer buffer;
    buffer.SerializeUInt32(messageLengthBE); // Serialize the message length in big-endian
    buffer.SerializeString(message); // Serialize the message content

    return buffer.GetData(); // Return the serialized data as a vector of characters
}

// Deserialize a message from a Buffer
std::string Protocol::DeserializeMessage(Buffer& buffer) {
    // Deserialize the message length in big-endian
    uint32_t messageLengthBE = buffer.DeserializeUInt32();

    // Convert the message length to host byte order
    uint32_t messageLength = ntohl(messageLengthBE);

    // Deserialize the message content
    std::string message = buffer.DeserializeString();

    return message; // Return the deserialized message
}
