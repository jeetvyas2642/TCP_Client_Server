#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Buffer.h"
#pragma comment(lib, "Ws2_32.lib")

class Protocol {
public:
    void send_message(SOCKET socket, const std::string& message);
    std::string receive_message(SOCKET socket);

private:
    Buffer buffer_;
};
