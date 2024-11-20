#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include "FIFOUtils.h"

void write_msg(int fd, message_t *m)
{
    if (write(fd, m, sizeof(message_t)) <= 0)
    {
        perror("Error writing to FIFO");
        exit(-1);
    }
}

int main()
{
    int fd;
    int key;
    message_t m;

    fd = write_FIFO(FIFO_LOCATION);

    printf("Enter a character: ");
    key = getchar();
    m.character = key;
    m.type = CONNECTION;

    write_msg(fd, &m);

    initscr();            /* Start curses mode 		*/
    cbreak();             /* Line buffering disabled	*/
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    noecho();             /* Don't echo() while we do getch */

    int ch;

    do
    {
        ch = getch();
        m.type = MOVEMENT;
        switch (ch)
        {
        case KEY_LEFT:
            m.direction = LEFT;
            break;
        case KEY_RIGHT:
            m.direction = RIGHT;
            break;
        case KEY_DOWN:
            m.direction = DOWN;
            break;
        case KEY_UP:
            m.direction = UP;
            break;
        default:
            m.type = NO_MOVEMENT;
            break;
        }
        refresh(); /* Print it on to the real screen */

        write_msg(fd, &m);

    } while (ch != 27);

    endwin(); /* End curses mode		  */

    return 0;
}