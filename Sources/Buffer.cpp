#include "Buffer.h"
#include <stdexcept>
#include <cstring>
#include <WinSock2.h>

Buffer::Buffer(std::size_t size)
    : buffer_(size), writeIndex_(0), readIndex_(0) {}

void Buffer::Grow() {
    buffer_.resize(buffer_.size() * 2);
}

void Buffer::SerializeUInt32(unsigned int value) {
    if (writeIndex_ + 4 > buffer_.size()) {
        Grow();
    }

    // Convert the value to network byte order (big-endian)
    value = htonl(value);
    std::memcpy(&buffer_[writeIndex_], &value, 4);
    writeIndex_ += 4;
}

unsigned int Buffer::DeserializeUInt32() {
    if (readIndex_ + 4 > buffer_.size()) {
        throw std::runtime_error("Buffer underflow");
    }

    unsigned int value;
    std::memcpy(&value, &buffer_[readIndex_], 4);
    readIndex_ += 4;

    // Convert the value from network byte order (big-endian) to host byte order
    return ntohl(value);
}

void Buffer::SerializeUInt16(unsigned short value) {
    if (writeIndex_ + 2 > buffer_.size()) {
        Grow();
    }

    // Convert the value to network byte order (big-endian)
    value = htons(value);
    std::memcpy(&buffer_[writeIndex_], &value, 2);
    writeIndex_ += 2;
}

unsigned short Buffer::DeserializeUInt16() {
    if (readIndex_ + 2 > buffer_.size()) {
        throw std::runtime_error("Buffer underflow");
    }

    unsigned short value;
    std::memcpy(&value, &buffer_[readIndex_], 2);
    readIndex_ += 2;

    // Convert the value from network byte order (big-endian) to host byte order
    return ntohs(value);
}

void Buffer::SerializeString(const std::string& value) {
    auto length = static_cast<unsigned int>(value.size());
    SerializeUInt32(length);

    if (writeIndex_ + length > buffer_.size()) {
        Grow();
    }

    std::memcpy(&buffer_[writeIndex_], value.data(), length);
    writeIndex_ += length;
}

std::string Buffer::DeserializeString() {
    auto length = DeserializeUInt32();

    if (readIndex_ + length > buffer_.size()) {
        throw std::runtime_error("Buffer underflow");
    }

    std::string value(&buffer_[readIndex_], length);
    readIndex_ += length;

    return value;
}
