/*#include "Client.h"
#include <iostream>
#include <string>

int main() {
    std::string serverAddress = "127.0.0.1";
    int serverPort = 8080;

    Client client(serverAddress, serverPort);

    if (!client.Connect()) {
        std::cout << "Failed to connect to server." << std::endl;
        return 1;
    }

    std::string roomName = "default_room";
    if (!client.JoinRoom(roomName)) {
        std::cout << "Failed to join room." << std::endl;
        return 1;
    }

    while (true) {
        std::string message;
        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        if (message == "quit") {
            break;
        }

        if (!client.SendMessageToRoom(roomName, message)) {
            std::cout << "Failed to send message." << std::endl;
        }

        std::string receivedMessage = client.ReceiveMessage();
        std::cout << "Received: " << receivedMessage << std::endl;
    }

    client.LeaveRoom(roomName);
    client.Disconnect();
    return 0;
}
*/