#include "Protocol.h"

void Protocol::send_message(SOCKET socket, const std::string& message) {
    uint32_t length = message.length();
    buffer_.serialize_uint32(length);
    buffer_.serialize_string(message);
    send(socket, buffer_.data(), buffer_.size(), 0);
}

std::string Protocol::receive_message(SOCKET socket) {
    char lengthBuffer[4];
    recv(socket, lengthBuffer, 4, 0);
    uint32_t length = *(uint32_t*)lengthBuffer;
    char* messageBuffer = new char[length];
    recv(socket, messageBuffer, length, 0);
    std::string message(messageBuffer, length);
    delete[] messageBuffer;
    return message;
}
