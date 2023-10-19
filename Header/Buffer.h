#pragma once
#include <string>

class Buffer {
public:
    Buffer(size_t size = 1024);
    ~Buffer();
    void serialize_uint32(uint32_t value);
    uint32_t deserialize_uint32();
    void serialize_uint16(uint16_t value);
    uint16_t deserialize_uint16();
    void serialize_string(const std::string& value);
    std::string deserialize_string(size_t length);
    size_t size() const;  
    char* data();  

private:
    void grow(size_t new_size);
    char* data_;
    size_t size_;
    size_t write_index_;
};
