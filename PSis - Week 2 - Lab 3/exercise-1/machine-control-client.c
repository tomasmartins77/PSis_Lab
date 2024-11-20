#include "remote-char.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "FIFOUtils.h"

direction_t random_direction()
{
    return random() % 4;
}

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

    int sleep_delay;
    m.type = MOVEMENT;
    while (1)
    {
        sleep_delay = random() % 700000;
        usleep(sleep_delay);

        m.direction = random_direction();

        write_msg(fd, &m);
    }

    return 0;
}