
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <zmq.h>
#include <assert.h>

#define WINDOW_SIZE 15

typedef struct ch_info_t
{
    int ch;
    int pos_x, pos_y;
} ch_info_t;

int main()
{
    ch_info_t char_data[100];
    for (int i = 0; i < 100; i++)
        char_data[i].ch = 0;
    int n_chars = 0;
    remote_char_t m;
    m.msg_type = 2;
    int fd;

    void *context = zmq_ctx_new();

    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");
    zmq_send(requester, &m, sizeof(m), 0);
    char ticket[100];
    zmq_recv(requester, ticket, sizeof(ticket), 0);

    int ticket_len = strnlen(ticket, sizeof(ticket));
    char *ticket_trimmed = (char *)malloc(ticket_len + 1);
    strncpy(ticket_trimmed, ticket, ticket_len);
    ticket_trimmed[ticket_len] = '\0';

    void *subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5556");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, ticket_trimmed, sizeof(ticket_trimmed));
    free(ticket_trimmed);

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    /* creates a window and draws a border */
    WINDOW *my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0, 0);
    wrefresh(my_win);
    direction_t direction;

    char type[7];
    while (1)
    {
        zmq_recv(subscriber, type, sizeof(type), 0);

        for (int i = 0; i < 100; i++)
        {
            if (char_data[i].ch == 0)
                break;

            /*deletes old place */
            wmove(my_win, char_data[i].pos_x, char_data[i].pos_y);
            waddch(my_win, ' ');
        }

        zmq_recv(subscriber, &char_data, sizeof(ch_info_t) * 100, 0);

        for (int i = 0; i < 100; i++)
        {
            if (char_data[i].ch == 0)
                break;
            /* draw mark on new position */
            wmove(my_win, char_data[i].pos_x, char_data[i].pos_y);
            waddch(my_win, char_data[i].ch | A_BOLD);
        }
        wrefresh(my_win);
    }
    endwin(); /* End curses mode		  */
    zmq_close(subscriber);
    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}