#include "Client.h"
#include <iostream>

Client::Client() {
    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        exit(1);
    }
}

Client::~Client() {
    WSACleanup();
}

void Client::connect_to_server() {
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);  // Assuming server is on port 8080

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        closesocket(sock);
        WSACleanup();
        exit(1);
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        exit(1);
    }

    // Example sending and receiving with the server
    const char* hello = "Hello from client";
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;
    char buffer[1024] = { 0 };
    int valread = recv(sock, buffer, 1024, 0);
    std::cout << buffer << std::endl;
    closesocket(sock);  // Don't forget to close the socket once done
}
