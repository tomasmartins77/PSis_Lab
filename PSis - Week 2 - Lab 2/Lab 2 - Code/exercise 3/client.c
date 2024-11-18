#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fdread(int fd);
int fdwrite(int fd);

int main()
{
    int fd_read, fd_write;
    char str[100];
    char response_str[100];
    int n;

    fd_write = fdwrite(fd_write);
    fd_read = fdread(fd_read);

    while (1)
    {
        printf("write a function:");
        fgets(str, 100, stdin);
        write(fd_write, str, 100);
        read(fd_read, response_str, 100);
        printf("result: %s\n", response_str);
    }
}

int fdread(int fd)
{
    while ((fd = open("/tmp/fifo_teste", O_RDONLY)) == -1)
    {
        if (mkfifo("/tmp/fifo_teste", 0666) != 0)
        {
            printf("problem creating the fifo\n");
            exit(-1);
        }
        else
        {
            printf("fifo created\n");
        }
    }
    printf("fifo just opened\n");
    return fd;
}

int fdwrite(int fd)
{
    while ((fd = open("/tmp/fifo_teste2", O_WRONLY)) == -1)
    {
        if (mkfifo("/tmp/fifo_teste2", 0666) != 0)
        {
            printf("problem creating the fifo\n");
            exit(-1);
        }
        else
        {
            printf("fifo created\n");
        }
    }
    printf("fifo just opened for writing\n");
    return fd;
}
