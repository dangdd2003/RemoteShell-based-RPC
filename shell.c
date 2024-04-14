#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 12345
#define BUFFER_SIZE 1024


void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0 && bytes_received == 0) {
            perror("Error receiving data from client");
            break;
        } else {
            // Process the received command
            if (strcmp(buffer, "quit") == 0) {
                // If the command is "quit", break out of the loop and close the client connection
                break;
            } else {
                // Otherwise, execute the command using system() function
                int result = system(buffer);
                if (result == -1) {
                    perror("Error executing command");
                }

                // Send the response back to the client
                send(client_socket, buffer, strlen(buffer), 0);
            }
        }
    }

    close(client_socket);
}

int main() {

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;
    // Set socket option to reuse address
    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("Error setting socket option");
        exit(1);
    }
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Bind socket to a specific port
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Error listening for connections");
        exit(1);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Accept a client connection
        client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
        if (client_socket < 0) {
            perror("Error accepting client connection");
            exit(1);
        }

        printf("Client connected\n");

        // Handle the client in a separate function
        handle_client(client_socket);
    }

    close(server_socket);

    return 0;
}
