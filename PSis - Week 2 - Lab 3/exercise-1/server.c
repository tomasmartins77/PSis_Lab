
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "FIFOUtils.h"
#include "remote-char.h"
#define WINDOW_SIZE 15

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

void receive_msg(int fd, message_t *m)
{
    if (read(fd, m, sizeof(message_t)) <= 0)
    {
        perror("Error reading from FIFO");
        exit(-1);
    }
}

int main()
{
    int fd;
    message_t m;

    fd = read_FIFO(FIFO_LOCATION);

    // ncurses initialization
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    /* creates a window and draws a border */
    WINDOW *my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0, 0);
    wrefresh(my_win);

    /* information about the character */
    int ch;
    int pos_x;
    int pos_y;

    direction_t direction;

    while (1)
    {
        receive_msg(fd, &m);

        if (m.type == CONNECTION)
        {
            ch = m.character;
            pos_x = WINDOW_SIZE / 2;
            pos_y = WINDOW_SIZE / 2;
        }

        // TODO_11
        // process the movement message
        if (m.type == MOVEMENT)
        {
            direction = m.direction;
            wmove(my_win, pos_x, pos_y);
            waddch(my_win, ' ');
            new_position(&pos_x, &pos_y, direction);
        }

        /* draw mark on new position */
        wmove(my_win, pos_x, pos_y);
        waddch(my_win, ch | A_BOLD);
        wrefresh(my_win);
    }
    endwin(); /* End curses mode		  */

    return 0;
}