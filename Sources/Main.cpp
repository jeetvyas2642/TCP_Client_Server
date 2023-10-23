#include <iostream>
#include <string>

// Include your Client and Server header files here
#include "Client.h"
#include "Server.h"

int main() {
    std::string choice;
    std::cout << "Do you want to run as a client or server? (Type 'client' or 'server'): ";
    std::cin >> choice;

    if (choice == "client") {
        // Configure the client parameters
        std::string serverAddress = "127.0.0.1"; // Set the server IP address
        int serverPort = 8080; // Set the server port

        // Create a Client instance
        Client client(serverAddress, serverPort);

        // Connect to the server
        if (!client.Connect()) {
            std::cout << "Failed to connect to the server." << std::endl;
            return 1;
        }

        std::string roomName = "default_room";

        // Join a room on the server
        if (!client.JoinRoom(roomName)) {
            std::cout << "Failed to join the room." << std::endl;
            return 1;
        }

        std::cin.ignore(); // Consume the newline character left in the input buffer

        std::string message;
        while (true) {
            std::cout << "Enter a message (type 'quit' to exit): ";
            std::getline(std::cin, message);

            if (message == "quit") {
                break;
            }

            // Send a message to the room on the server
            if (!client.SendMessageToRoom(roomName, message)) {
                std::cout << "Failed to send the message." << std::endl;
            }

            // Receive and display the response from the server
            std::string receivedMessage = client.ReceiveData();
            std::cout << "Received: " << receivedMessage << std::endl;
        }

        // Leave the room on the server
        client.LeaveRoom(roomName);

        // Disconnect from the server
        client.Disconnect();
    }
    else if (choice == "server") {
        // Configure the server parameters
        int port = 8080; // Set the server port

        // Create a Server instance and start the server
        Server server(port);
        server.Start();
    }
    else {
        std::cout << "Invalid choice. Exiting.";
        return 1;
    }

    return 0;
}
