
#include "../remote-char.h"

#include <stdlib.h>

#include <zmq.h>
#include "zhelpers.h"
#include <ncurses.h>
#include "../balls.pb-c.h"

#define WINDOW_SIZE 15

typedef struct ch_info_t
{
    int ch;
    int pos_x, pos_y;
} ch_info_t;

direction_t random_direction()
{
    return random() % 4;
}
void new_position(int *x, int *y, direction_t direction)
{
    switch (direction)
    {
    case UP:
        (*x)--;
        if (*x == 0)
            *x = 2;
        break;
    case DOWN:
        (*x)++;
        if (*x == WINDOW_SIZE - 1)
            *x = WINDOW_SIZE - 3;
        break;
    case LEFT:
        (*y)--;
        if (*y == 0)
            *y = 2;
        break;
    case RIGHT:
        (*y)++;
        if (*y == WINDOW_SIZE - 1)
            *y = WINDOW_SIZE - 3;
        break;
    default:
        break;
    }
}

int find_ch_info(ch_info_t char_data[], int n_char, int ch)
{

    for (int i = 0; i < n_char; i++)
    {
        if (ch == char_data[i].ch)
        {
            return i;
        }
    }
    return -1;
}

void zmq_send_BallDrawDisplayMsg(void *publisher, char ch, int x, int y, int random_secret)
{

    zmq_send(publisher, &random_secret, sizeof(random_secret), ZMQ_SNDMORE);

    BallDrawDisplayMsg pb_m_stuct = BALL_DRAW_DISPLAY_MSG__INIT;
    pb_m_stuct.ch.data = malloc(sizeof(ch));
    memcpy(pb_m_stuct.ch.data, &ch, sizeof(ch));
    pb_m_stuct.ch.len = sizeof(ch);
    pb_m_stuct.x = x;
    pb_m_stuct.y = y;

    int size_bin_msg = ball_draw_display_msg__get_packed_size(&pb_m_stuct);
    char *pb_m_bin = malloc(size_bin_msg);
    ball_draw_display_msg__pack(&pb_m_stuct, pb_m_bin);

    zmq_send(publisher, pb_m_bin, size_bin_msg, 0);
    // free(pb_m_bin);
    // free(pb_m_stuct.ch.data);
}

int main()
{
    zmq_msg_t zmq_msg;
    zmq_msg_init(&zmq_msg);
    PayperviewReq *req;
    MovementReq *move_req;
    ClientConnectionReq *client_req;
    PayperviewResp resp = PAYPERVIEW_RESP__INIT;
    // STEP 2
    ch_info_t char_data[100];
    int n_chars = 0;
    int fd;

    void *context = zmq_ctx_new();
    void *responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:55555");
    if (rc != 0)
    {
        printf("error binding REP socket");
        exit(-1);
    }

    void *publisher = zmq_socket(context, ZMQ_PUB);
    rc = zmq_bind(publisher, "tcp://*:55556");
    if (rc != 0)
    {
        printf("error binding PUB socket");
        exit(-1);
    }

    int random_secret = random();

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    /* creates a window and draws a border */
    WINDOW *my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0, 0);
    wrefresh(my_win);

    int ch;
    int pos_x;
    int pos_y;

    direction_t direction;
    while (1)
    {
        int msg_type = 2;
        zmq_recv(responder, &msg_type, sizeof(msg_type), 0);

        if (msg_type == 2)
        {
            // verify credit card

            // TODO 3 - processe the payperview_req message
            //          replace the zmq_recv by a zmq_recvmsg
            //          get the message buffer with zmq_msg_data
            //          get the C message structure with the payperview_req__unpack
            int msg_len = zmq_recvmsg(responder, &zmq_msg, 0);
            // TODO 3
            void *msg_data = zmq_msg_data(&zmq_msg);
            req = payperview_req__unpack(NULL, msg_len, msg_data);

            // VERIFY if CC correct
            if (strcmp(req->credit_card_number, "999123222222") != 0)
            {
                // TODO 4 –  send the reply as a protocol buffer payperview_resp message
                resp.secret = random_secret;
                size_t resp_size = payperview_resp__get_packed_size(&resp);
                void *resp_buf = malloc(resp_size);
                payperview_resp__pack(&resp, resp_buf);
                zmq_send(responder, resp_buf, resp_size, 0);
                free(resp_buf);
                continue;
            }
        }
        if (msg_type == 0)
        {
            // TODO 8 - read and process the client_connection_req message
            int msg_len = zmq_recvmsg(responder, &zmq_msg, 0);
            void *msg_data = zmq_msg_data(&zmq_msg);
            client_req = client_connection_req__unpack(NULL, msg_len, msg_data);

            pos_x = WINDOW_SIZE / 2;
            pos_y = WINDOW_SIZE / 2;

            char_data[n_chars].ch = client_req->client_id;
            char_data[n_chars].pos_x = pos_x;
            char_data[n_chars].pos_y = pos_y;
            n_chars++;
            zmq_send_BallDrawDisplayMsg(publisher, client_req->client_id, pos_x, pos_y, random_secret);
        }
        if (msg_type == 1)
        {
            // TODO 11 - read and process the movement_req message
            int msg_len = zmq_recvmsg(responder, &zmq_msg, 0);
            void *msg_data = zmq_msg_data(&zmq_msg);
            move_req = movement_req__unpack(NULL, msg_len, msg_data);

            int ch_pos = find_ch_info(char_data, n_chars, move_req->client_id);
            if (ch_pos != -1)
            {
                pos_x = char_data[ch_pos].pos_x;
                pos_y = char_data[ch_pos].pos_y;
                ch = char_data[ch_pos].ch;
                /*deletes old place */
                wmove(my_win, pos_x, pos_y);
                waddch(my_win, ' ');
                zmq_send_BallDrawDisplayMsg(publisher, ' ', pos_x, pos_y, random_secret);
                /* claculates new direction */
                direction = move_req->direction;

                /* claculates new mark position */
                new_position(&pos_x, &pos_y, direction);
                char_data[ch_pos].pos_x = pos_x;
                char_data[ch_pos].pos_y = pos_y;
                zmq_send_BallDrawDisplayMsg(publisher, ch, pos_x, pos_y, random_secret);
            }
        }
        /* draw mark on new position */
        wmove(my_win, pos_x, pos_y);
        waddch(my_win, ch | A_BOLD);
        wrefresh(my_win);

        s_send(responder, "OK");
    }
    endwin(); /* End curses mode		  */

    return 0;
}