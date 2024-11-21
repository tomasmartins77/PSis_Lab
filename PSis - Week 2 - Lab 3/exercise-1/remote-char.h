#ifndef REMOTE_CHAR_H
#define REMOTE_CHAR_H
#include <ncurses.h>

typedef enum direction_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} direction_t;

typedef enum message_type_t
{
    CONNECTION,
    MOVEMENT,
    NO_MOVEMENT,
} message_type_t;

typedef struct
{
    char character;
    message_type_t type;
    direction_t direction;
} message_t;

typedef struct
{
    int x;
    int y;
    char character;
} player_t;

#define FIFO_LOCATION "/tmp/lab3_fifo"

#endif