#include "Client.h"
#include "Server.h"
#include <iostream>

int main() {
    std::cout << "1. Start Server" << std::endl;
    std::cout << "2. Start Client" << std::endl;
    std::cout << "Enter choice: ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        Server server;
        server.start();
    }
    else if (choice == 2) {
        Client client;
        client.connect_to_server();
    }
    else {
        std::cerr << "Invalid choice" << std::endl;
    }
    return 0;
}
