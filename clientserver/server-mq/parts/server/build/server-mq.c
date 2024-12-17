#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <time.h>

#define QUEUE_NAME "/my_queue"
#define BUFFER_SIZE 400

double get_time_in_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
    mqd_t mq;
    char buffer[BUFFER_SIZE];
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = BUFFER_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("Server: mq_open");
        exit(EXIT_FAILURE);
    }

    printf("Server: Waiting for messages...\n");

    double start_time = get_time_in_seconds();
    ssize_t bytes_received = mq_receive(mq, buffer, BUFFER_SIZE, NULL);
    double end_time = get_time_in_seconds();

    if (bytes_received == -1) {
        perror("Server: mq_receive");
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        exit(EXIT_FAILURE);
    }

    printf("Server: Received message of %ld bytes\n", bytes_received);
    printf("Elapsed Time: %.6f seconds\n", end_time - start_time);
    printf("Throughput: %.2f bytes/second\n", bytes_received / (end_time - start_time));

    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}

