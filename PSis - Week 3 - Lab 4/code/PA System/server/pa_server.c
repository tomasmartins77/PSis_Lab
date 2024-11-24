#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include "zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();
    // Bind a ZMQ_REP socket
    void *responder = zmq_socket(context, ZMQ_REP);
    int rc_res = zmq_bind(responder, "ipc:///tmp/s1");
    assert(rc_res == 0);

    // Bind a ZMQ_PUB socket
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int rc_pub = zmq_bind(publisher, "tcp://*:5556");
    assert(rc_pub == 0);

    while (1)
    {
        // receive messages from the microphones
        char *dpt = s_recv(responder);
        char *s = s_recv(responder);
        printf("department %s message %s", dpt, s);
        s_send(responder, "OK");
        // publish message to speakers
        s_sendmore(publisher, dpt);
        s_send(publisher, s);
        free(dpt);
        free(s);
    }
    zmq_close(publisher);
    zmq_close(responder);
    zmq_ctx_destroy(context);
    return 0;
}