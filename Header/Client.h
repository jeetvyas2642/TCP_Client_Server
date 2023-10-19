#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

class Client {
public:
    Client();
    ~Client();
    void connect_to_server();

private:
    WSADATA wsaData;
    SOCKET sock;
};
