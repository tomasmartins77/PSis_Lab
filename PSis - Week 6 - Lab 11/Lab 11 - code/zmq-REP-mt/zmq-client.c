//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int vector[100];
pthread_mutex_t mutex;

void *thread_function(void *arg)
{
    char buffer[100];
    fgets(buffer, 100, stdin);
    if (strcmp(buffer, "exit\n") == 0)
    {
        for (int i = 0; i < 100; i++)
        {
            pthread_mutex_lock(&mutex);
            if (vector[i] == 0)
                break;
            printf("%d, ", vector[i]);
            pthread_mutex_unlock(&mutex);
        }
        exit(0);
    }
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    void *context = zmq_ctx_new();

    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "ipc:///tmp/fifo-pipe-front-end");
    int n;
    int resp;

    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, (void *)1);

    int pos = 0;
    while (1)
    {
        n = rand() % 10;
        printf("Sending %d\n", n);
        zmq_send(requester, &n, sizeof(n), 0);

        zmq_recv(requester, &resp, sizeof(resp), 0);
        if (resp)
        {
            printf("%d is prime\n", n);
            vector[pos] = n;
            pos++;
        }
        else
        {
            printf("%d is NOT prime\n", n);
        }
        sleep(1);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}