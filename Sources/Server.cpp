#include "Server.h"
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <vector>

// Constructor for the Server class
Server::Server(int port) : port_(port), sockfd_(INVALID_SOCKET) {}

// Destructor for the Server class
Server::~Server() {
    if (sockfd_ != INVALID_SOCKET) {
        closesocket(sockfd_);
    }
}

// Start the server
void Server::Start() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << "\n";
        return;
    }

    sockfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd_ == INVALID_SOCKET) {
        std::cerr << "Could not create socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port_);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd_, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << "\n";
        closesocket(sockfd_);
        WSACleanup();
        return;
    }

    if (listen(sockfd_, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << "\n";
        closesocket(sockfd_);
        WSACleanup();
        return;
    }

    std::cout << "Server is running...\n";

    while (true) {
        SOCKET clientSock = accept(sockfd_, NULL, NULL);
        if (clientSock == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << "\n";
            continue;
        }

        clientSocks_.push_back(clientSock); // Store the client socket

        std::cout << "Client connected.\n";

        std::thread clientThread(&Server::HandleClient, this, clientSock);
        clientThread.detach();
    }
}

// Handle communication with a client
void Server::HandleClient(SOCKET clientSock) {
    char buffer[513];  // Increase buffer size to 513 to make room for the null-terminator
    std::string partialMessage = "";
    while (true) {
        int bytesReceived = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';  // Null-terminate received data
            partialMessage += buffer;

            // Check for newline character to process a complete message
            size_t newlinePos = partialMessage.find('\n');
            while (newlinePos != std::string::npos) {
                std::string message = partialMessage.substr(0, newlinePos);
                partialMessage = partialMessage.substr(newlinePos + 1);
                std::cout << "Received from client: " << message << "\n";

                // Broadcast the received message to all clients (except the sender)
                BroadcastMessage(clientSock, message.c_str());

                // Check for more complete messages in the remaining data
                newlinePos = partialMessage.find('\n');
            }
        }
        else if (bytesReceived == 0) {
            std::cout << "Client disconnected.\n";

            // Remove the client socket from the list
            for (auto it = clientSocks_.begin(); it != clientSocks_.end(); ++it) {
                if (*it == clientSock) {
                    clientSocks_.erase(it);
                    break;
                }
            }

            closesocket(clientSock);
            break;
        }
        else {
            std::cerr << "recv failed: " << WSAGetLastError() << "\n";
            closesocket(clientSock);
            break;
        }
    }
}

// Broadcast a message to all connected clients (except the sender)
void Server::BroadcastMessage(SOCKET senderSock, const char* message) {
    std::string messageWithNewline = std::string(message) + "\n"; // Add a newline character
    for (SOCKET clientSock : clientSocks_) {
        if (clientSock != senderSock) {
            send(clientSock, messageWithNewline.c_str(), messageWithNewline.size(), 0);
        }
    }
}
