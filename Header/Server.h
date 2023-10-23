#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <WinSock2.h>

class Server {
public:
    // Constructor that takes a port number
    Server(int port);

    // Destructor
    ~Server();

    // Start the server
    void Start();

private:
    int port_;                  // Port number on which the server listens
    SOCKET sockfd_;             // Server socket descriptor
    std::vector<SOCKET> clientSocks_; // List of connected client sockets

    // Handle communication with a client
    void HandleClient(SOCKET clientSock);

    // Broadcast a message to all clients except the sender
    void BroadcastMessage(SOCKET senderSock, const char* message);
};

#endif // SERVER_H
