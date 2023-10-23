#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>

class Buffer {
public:
    // Default constructor with a default size
    Buffer(std::size_t size = 256);

    // Function to grow the buffer size
    void Grow();

    // Serialize and deserialize functions for unsigned int
    void SerializeUInt32(unsigned int value);
    unsigned int DeserializeUInt32();

    // Serialize and deserialize functions for unsigned short
    void SerializeUInt16(unsigned short value);
    unsigned short DeserializeUInt16();

    // Serialize and deserialize functions for strings
    void SerializeString(const std::string& value);
    std::string DeserializeString();

    // Get the data as a std::vector<char>
    std::vector<char> GetData() const {
        return buffer_;
    }

    // Get the current size of the buffer
    std::size_t GetSize() const {
        return buffer_.size();
    }

private:
    std::vector<char> buffer_;  // Internal buffer to store data
    std::size_t writeIndex_;    // Index to write data
    std::size_t readIndex_;     // Index to read data
};

#endif // BUFFER_H
