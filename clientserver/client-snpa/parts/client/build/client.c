#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 400  // Buffer size for the message

double get_time_in_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message[BUFFER_SIZE];
    char buffer[BUFFER_SIZE] = {0};

    // Create a message of 400 bytes
    snprintf(message, BUFFER_SIZE, "This is a 400-byte test message from the client. %*s", 400 - 53, "");

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Measure the time to send and receive data
    double start_time = get_time_in_seconds();

    // Send 400-byte message
    int bytes_sent = send(sock, message, BUFFER_SIZE, 0);
    if (bytes_sent != BUFFER_SIZE) {
        perror("Failed to send message");
    }

    // Receive response from the server
    int bytes_received = read(sock, buffer, BUFFER_SIZE);
    if (bytes_received < 0) {
        perror("Failed to receive message");
    }

    double end_time = get_time_in_seconds();

    // Calculate throughput
    double elapsed_time = end_time - start_time;
    double throughput = (bytes_sent + bytes_received) / elapsed_time;

    printf("Total Bytes Transferred: %d\n", bytes_sent + bytes_received);
    printf("Elapsed Time: %.6f seconds\n", elapsed_time);
    printf("Throughput: %.2f bytes/second\n", throughput);

    close(sock);

    return 0;
}

