#include "Server.h"
#include <iostream>
#include <thread>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

Server::Server() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    WSACleanup();
}

void Server::start() {
    struct addrinfo* result = NULL, hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int iResult = getaddrinfo(NULL, "8080", &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed: " << iResult << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    server_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    iResult = bind(server_socket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    iResult = listen(server_socket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    while (true) {
        SOCKET client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
            closesocket(server_socket);
            WSACleanup();
            exit(EXIT_FAILURE);
        }

        std::thread client_thread(&Server::handle_client, this, client_socket);
        client_thread.detach();
    }
}

void Server::handle_client(SOCKET client_socket) {
    char buffer[1024] = { 0 };
    int valread;
    while ((valread = recv(client_socket, buffer, 1024, 0)) > 0) {
        send(client_socket, buffer, valread, 0);
    }
    closesocket(client_socket);
}
