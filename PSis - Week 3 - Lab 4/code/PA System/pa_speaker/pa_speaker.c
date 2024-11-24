#include <stdio.h>
#include <zmq.h>
#include <string.h>
#include "zhelpers.h"

int main()
{
    char line[100];
    char dpt_name[100];
    printf("What is the department of this building? (DEEC, DEI, ...)");
    fgets(line, 100, stdin);
    sscanf(line, "%s", dpt_name);
    printf("We will broadcast all messages from the president of IST and %s\n", dpt_name);

    void *context = zmq_ctx_new();
    // Connect to the server using ZMQ_SUB
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5556");

    // subscribe to topics
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, dpt_name, strlen(dpt_name));
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "President", 9);

    while (1)
    {
        // receive messages
        char *dpt = s_recv(subscriber);
        char *string = s_recv(subscriber);
        printf("message from  %s - %s", dpt, string);
        free(string);
        free(dpt);
    }
}