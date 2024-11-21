
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

void update_window(WINDOW *my_win, int x, int y, char character)
{
    wmove(my_win, x, y);
    waddch(my_win, character);
}

void create_player(char character, player_t *players, int n_players, WINDOW *my_win)
{
    players[n_players].x = WINDOW_SIZE / 2;
    players[n_players].y = WINDOW_SIZE / 2;
    players[n_players].character = character;
    update_window(my_win, players[n_players].x, players[n_players].y, character | A_BOLD);
}

int search_player(player_t *players, int n_players, char character)
{
    for (int i = 0; i < n_players; i++)
    {
        if (players[i].character == character)
        {
            return i;
        }
    }
}

void handle_movement(message_t m, player_t *players, int n_players, WINDOW *my_win)
{
    int player_index = search_player(players, n_players, m.character);
    player_t *current_player = &players[player_index];
    update_window(my_win, current_player->x, current_player->y, ' '); // remove mark from old position
    new_position(&current_player->x, &current_player->y, m.direction);
    update_window(my_win, current_player->x, current_player->y, current_player->character | A_BOLD); // draw mark on new position
}

void handle_connection(message_t m, player_t *players, int *n_players, WINDOW *my_win)
{
    create_player(m.character, players, *n_players, my_win);
    *n_players += 1;
}

int main()
{
    int fd;
    int n_players = 0;
    int player_index = 0;
    message_t m;
    /* information about the characters */
    player_t players[10];
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
            handle_connection(m, players, &n_players, my_win);
        }
        else if (m.type == MOVEMENT)
        {
            handle_movement(m, players, n_players, my_win);
        }
        wrefresh(my_win);
    }
    endwin(); /* End curses mode */

    return 0;
}