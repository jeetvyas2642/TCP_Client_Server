#pragma once
#include <WinSock2.h>
#include <string>

class Server {
public:
    Server();
    ~Server();
    void start();
    void handle_client(SOCKET client_socket);

private:
    SOCKET server_socket;
};
