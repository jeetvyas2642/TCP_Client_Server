#include "Buffer.h"
#include <stdexcept>

Buffer::Buffer(size_t size) : data_(new char[size]), size_(size), write_index_(0) {
    // ...
}

Buffer::~Buffer() {  // Defining destructor here
    delete[] data_;
}

size_t Buffer::size() const {
    return write_index_;  // Return the write index as the current size of the buffer
}

char* Buffer::data() {
    return data_;  // Return the data pointer
}

void Buffer::grow(size_t new_size) {
    char* new_data = new char[new_size];
    memcpy(new_data, data_, size_);
    delete[] data_;
    data_ = new_data;
    size_ = new_size;
}

void Buffer::serialize_uint32(uint32_t value) {
    if (write_index_ + 4 > size_) grow(size_ * 2);
    data_[write_index_++] = (value >> 24) & 0xFF;
    data_[write_index_++] = (value >> 16) & 0xFF;
    data_[write_index_++] = (value >> 8) & 0xFF;
    data_[write_index_++] = value & 0xFF;
}

uint32_t Buffer::deserialize_uint32() {
    if (write_index_ + 4 > size_) throw std::runtime_error("Not enough data");
    uint32_t value = (static_cast<uint32_t>(data_[write_index_++]) << 24) |
        (static_cast<uint32_t>(data_[write_index_++]) << 16) |
        (static_cast<uint32_t>(data_[write_index_++]) << 8) |
        static_cast<uint32_t>(data_[write_index_++]);
    return value;
}

void Buffer::serialize_uint16(uint16_t value) {
    if (write_index_ + 2 > size_) grow(size_ * 2);
    data_[write_index_++] = (value >> 8) & 0xFF;
    data_[write_index_++] = value & 0xFF;
}

uint16_t Buffer::deserialize_uint16() {
    if (write_index_ + 2 > size_) throw std::runtime_error("Not enough data");
    uint16_t value = (static_cast<uint16_t>(data_[write_index_++]) << 8) |
        static_cast<uint16_t>(data_[write_index_++]);
    return value;
}

void Buffer::serialize_string(const std::string& value) {
    size_t length = value.length();
    if (write_index_ + length > size_) grow(size_ + length);
    memcpy(data_ + write_index_, value.data(), length);
    write_index_ += length;
}

std::string Buffer::deserialize_string(size_t length) {
    if (write_index_ + length > size_) throw std::runtime_error("Not enough data");
    std::string value(data_ + write_index_, length);
    write_index_ += length;
    return value;
}
