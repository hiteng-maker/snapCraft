#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 400  // Buffer size for the message

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[BUFFER_SIZE];
    char buffer[BUFFER_SIZE] = {0};

    // Create the message to send
    snprintf(message, BUFFER_SIZE, "This is a test message from the client. It is designed to be exactly 400 bytes. %*s", 400 - 83, ""); // Fill to make 400 bytes

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Send 400 bytes to the server
    send(sock, message, BUFFER_SIZE, 0);
    printf("400-byte message sent to server\n");

    // Read response from the server
    int bytes_read = read(sock, buffer, BUFFER_SIZE);
    if (bytes_read < 0) {
        perror("Read failed");
    } else {
        printf("Server: %.*s\n", bytes_read, buffer);
    }

    close(sock);

    return 0;
}

