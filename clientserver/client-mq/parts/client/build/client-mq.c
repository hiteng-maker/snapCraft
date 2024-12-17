#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <time.h>

#define QUEUE_NAME "/my_queue"
#define BUFFER_SIZE 400
#define PRIORITY 0

double get_time_in_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    mqd_t mq;
    char message[BUFFER_SIZE];

    snprintf(message, BUFFER_SIZE, "This is a 400-byte test message. %*s", 400 - 37, "");

    mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == (mqd_t)-1) {
        perror("Client: mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Client: Sending message...\n");

    double start_time = get_time_in_seconds();
    if (mq_send(mq, message, BUFFER_SIZE, PRIORITY) == -1) {
        perror("Client: mq_send");
        mq_close(mq);
        exit(EXIT_FAILURE);
    }
    double end_time = get_time_in_seconds();

    printf("Elapsed Time: %.6f seconds\n", end_time - start_time);
    printf("Throughput: %.2f bytes/second\n", BUFFER_SIZE / (end_time - start_time));

    mq_close(mq);
    return 0;
}

