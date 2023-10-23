#include "Client.h"
#include <Winsock2.h>
#include <iostream>
#include <thread>
#include <Ws2tcpip.h>
#include "Buffer.h"
#include "Protocol.h"

#pragma comment(lib, "Ws2_32.lib")

// Constructor
Client::Client(const std::string& serverAddress, int serverPort)
    : serverAddress_(serverAddress), serverPort_(serverPort), sockfd_(-1) {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
    }
}

// Destructor
Client::~Client() {
    Disconnect();
    WSACleanup();
}

// Connect to the server
bool Client::Connect() {
    Disconnect();
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ == INVALID_SOCKET) {
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort_);
    inet_pton(AF_INET, serverAddress_.c_str(), &serverAddr.sin_addr);

    if (connect(sockfd_, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        return false;
    }

    return true;
}

// Disconnect from the server
void Client::Disconnect() {
    if (sockfd_ != INVALID_SOCKET) {
        closesocket(sockfd_);
        sockfd_ = INVALID_SOCKET;
    }
}

// Send data to the server
bool Client::SendData(const std::string& data) {
    if (sockfd_ == INVALID_SOCKET) {
        return false;
    }

    std::string dataWithNewline = data + '\n'; // Add a newline character at the end

    if (send(sockfd_, dataWithNewline.c_str(), static_cast<int>(dataWithNewline.size()), 0) == -1) {
        return false;
    }

    return true;
}

// Receive data from the server
std::string Client::ReceiveData() {
    char buffer[257]; // One more byte for null-termination
    int bytesReceived = recv(sockfd_, buffer, sizeof(buffer) - 1, 0); // Save room for null-terminator

    if (bytesReceived <= 0) {
        return "";
    }

    buffer[bytesReceived] = '\0'; // Null-terminate the string
    return std::string(buffer);
}

// Join a room on the server
bool Client::JoinRoom(const std::string& roomName) {
    Buffer buffer(256);
    buffer.SerializeString("JOIN");
    buffer.SerializeString(roomName);

    std::vector<char> vecData = buffer.GetData();
    const char* dataToSend = vecData.data(); // Get the pointer to the data

    if (SendData(dataToSend)) {
        return true;
    }

    return false;
}

// Leave a room on the server
bool Client::LeaveRoom(const std::string& roomName) {
    Buffer buffer(256);
    buffer.SerializeString("LEAVE");
    buffer.SerializeString(roomName);

    std::vector<char> dataVector = buffer.GetData();  // Get the data as a vector
    const char* dataToSend = dataVector.data();       // Convert vector data to const char*

    if (SendData(dataToSend)) {
        return true;
    }

    return false;
}

// Send a message to a room on the server
bool Client::SendMessageToRoom(const std::string& roomName, const std::string& message) {
    Buffer buffer(256);
    buffer.SerializeString("MESSAGE");
    buffer.SerializeString(roomName);
    buffer.SerializeString(message);

    std::vector<char> dataVector = buffer.GetData();  // Get the data as a vector
    const char* dataToSend = dataVector.data();       // Convert vector data to const char*

    if (SendData(dataToSend)) {
        return true;
    }

    return false;
}
