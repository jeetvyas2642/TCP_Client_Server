# Chat Application with Client-Server Architecture

This is a simple chat application implemented using a client-server architecture. It allows clients to connect to a server, join chat rooms, send messages, and receive messages from other clients in the same room.

## Prerequisites

Before running the application, ensure you have the following prerequisites installed:

- [Visual Studio](https://visualstudio.microsoft.com/downloads/) (for Windows) or a C++ compiler (for other platforms).
- [WinSock2 Library](https://docs.microsoft.com/en-us/windows/win32/winsock/installing-the-ws2_32-libraries) for Windows platform.
- CMake (optional for building and compiling).

## Project Structure

The project consists of the following components:

- `Client`: Contains the client-side code for connecting to the server and sending/receiving messages.
- `Server`: Contains the server-side code for handling client connections, chat rooms, and message broadcasting.
- `Buffer`: A utility class for serializing and deserializing data.
- `Protocol`: Defines the message serialization and deserialization protocol.
- `Utility`: Contains utility functions for working with endianess and string splitting.

## Usage

1. Compile the project using your preferred C++ compiler or IDE.

2. Run the server:

   ```bash
   ./Server.exe

Note: You've to run two or more output windows for running server(s) and client(s). Run only from .sln project file. Ignore any source file you may find outside the VS project file.
