#include "../remote-char.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include <zmq.h>
#include "zhelpers.h"
#include "../balls.pb-c.h"

int main()
{
    MovementReq move_req = MOVEMENT_REQ__INIT;
    ClientConnectionReq client_req = CLIENT_CONNECTION_REQ__INIT;
    void *context = zmq_ctx_new();
    void *requester = zmq_socket(context, ZMQ_REQ);
    int rc = zmq_connect(requester, "tcp://localhost:55555");
    if (rc != 0)
    {
        printf("error connecting REQ socket");
        exit(-1);
    }
    printf("socket connected\n");

    char ch;
    do
    {
        printf("what is your symbol(a..z)?: ");
        ch = getchar();
        ch = tolower(ch);
    } while (!isalpha(ch));

    int msg_type = 0;
    zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);

    // TODO 7 - create and fill a message of type  client_connection_req
    //           and send the packed message to the server
    client_req.client_id = ch;
    size_t req_size = client_connection_req__get_packed_size(&client_req);
    char *req_buf = malloc(req_size);
    client_connection_req__pack(&client_req, req_buf);
    zmq_send(requester, req_buf, req_size, 0);
    free(req_buf);

    char *str = s_recv(requester);
    free(str);

    int sleep_delay;
    direction_t direction;
    int n = 0;
    while (1)
    {
        n++;
        sleep_delay = random() % 700000;
        usleep(sleep_delay);
        direction = random() % 4;
        switch (direction)
        {
        case LEFT:
            printf("%d Going Left   \n", n);
            break;
        case RIGHT:
            printf("%d Going Right   \n", n);
            break;
        case DOWN:
            printf("%d Going Down   \n", n);
            break;
        case UP:
            printf("%d Going Up    \n", n);
            break;
        }

        int msg_type = 1;
        zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);

        // TODO 10 - create and fill a message of type  movement_req
        //           and send the packed message to the server
        move_req.client_id = ch;
        move_req.direction = direction;
        size_t req_size = movement_req__get_packed_size(&move_req);
        char *req_buf = malloc(req_size);
        movement_req__pack(&move_req, req_buf);
        zmq_send(requester, req_buf, req_size, 0);
        free(req_buf);

        char *str = s_recv(requester);
        free(str);
    }

    return 0;
}