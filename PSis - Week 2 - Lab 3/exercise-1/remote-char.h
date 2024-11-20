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

// TODO_1
// declaration the struct corresponding to the exchanged messages
typedef struct
{
    char character;
    message_type_t type;
    direction_t direction;
} message_t;

// TODO_2
// declaration of the FIFO location
#define FIFO_LOCATION "/tmp/lab3_fifo"

#endif