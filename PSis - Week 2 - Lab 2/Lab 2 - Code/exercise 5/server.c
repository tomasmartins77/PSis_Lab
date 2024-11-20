#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include "data_struct.h"

int fdread(int fd);
int fdwrite(int fd);

int main()
{
    int fd_read, fd_write;
    void *lib;
    int (*fcn)();
    int n;
    char str[100];
    int response;
    char response_str[100];
    message_type msg;

    fd_read = fdread(fd_read);
    fd_write = fdwrite(fd_write + 1);

    // Load the shared library
    lib = dlopen("./funcs.so", RTLD_LAZY);
    if (!lib)
    {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        n = read(fd_read, &msg, sizeof(msg));
        if (n <= 0)
        {
            perror("read ");
            exit(-1);
        }
        char *newline = strchr(msg.f_name, '\n');
        if (newline)
        {
            *newline = '\0';
        }
        // Load func from the loaded library
        fcn = dlsym(lib, msg.f_name);
        if (fcn == NULL)
        {
            printf("Function not found\n");
            continue;
        }
        if (msg.funct_type == 3)
        {
            response = fcn(msg.arg);
        }
        else
        {
            response = fcn();
        }

        sprintf(response_str, "%d", response);
        write(fd_write, response_str, strlen(response_str) + 1);
    }
    close(fd_read);
    close(fd_write);
    printf("fifo aberto\n");
}

int fdread(int fd)
{
    while ((fd = open("/tmp/fifo_teste2", O_RDONLY)) == -1)
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
    printf("fifo just opened\n");
    return fd;
}

int fdwrite(int fd)
{
    while ((fd = open("/tmp/fifo_teste", O_WRONLY)) == -1)
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
    printf("fifo just opened for writing\n");
    return fd;
}