
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

void create_player(char character, char_info_t *players, int n_players)
{
    players[n_players].x = WINDOW_SIZE / 2;
    players[n_players].y = WINDOW_SIZE / 2;
    players[n_players].character = character;
}

int search_player(char_info_t *players, int n_players, char character)
{
    for (int i = 0; i < n_players; i++)
    {
        if (players[i].character == character)
        {
            return i;
        }
    }
}

int main()
{
    int fd;
    int n_players = 0;
    int player_index = 0;
    message_t m;
    /* information about the characters */
    char_info_t players[10];
    char_info_t current_player;
    direction_t direction;

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

    while (1)
    {
        receive_msg(fd, &m);

        if (m.type == CONNECTION)
        {
            create_player(m.character, players, n_players);
            current_player = players[n_players];
            n_players++;
        }
        else if (m.type == MOVEMENT)
        {
            direction = m.direction;
            player_index = search_player(players, n_players, m.character);
            current_player = players[player_index];
            wmove(my_win, current_player.x, current_player.y);
            waddch(my_win, ' ');
            new_position(&current_player.x, &current_player.y, direction);
            players[player_index] = current_player;
        }

        /* draw mark on new position */
        wmove(my_win, current_player.x, current_player.y);
        waddch(my_win, current_player.character | A_BOLD);
        wrefresh(my_win);
    }
    endwin(); /* End curses mode */

    return 0;
}