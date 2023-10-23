#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    // Constructor to initialize the client with server address and port
    Client(const std::string& serverAddress, int serverPort);

    // Destructor to clean up resources when the client is destroyed
    ~Client();

    // Connect to the server
    bool Connect();

    // Disconnect from the server
    void Disconnect();

    // Send data to the server
    bool SendData(const std::string& data);

    // Receive data from the server
    std::string ReceiveData();

    // Join a chat room on the server
    bool JoinRoom(const std::string& roomName);

    // Leave a chat room on the server
    bool LeaveRoom(const std::string& roomName);

    // Send a message to a chat room on the server
    bool SendMessageToRoom(const std::string& roomName, const std::string& message);

private:
    int sockfd_;            // Socket file descriptor
    std::string serverAddress_;  // Server address
    int serverPort_;        // Server port
};

#endif // CLIENT_H
