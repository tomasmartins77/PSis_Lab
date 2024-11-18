#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

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

    fd_read = fdread(fd_read);
    fd_write = fdwrite(fd_write);

    // Load the shared library
    lib = dlopen("./funcs.so", RTLD_LAZY);
    if (!lib)
    {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        n = read(fd_read, str, 100);
        if (n <= 0)
        {
            perror("read ");
            exit(-1);
        }

        // Remove newline character if present
        char *newline = strchr(str, '\n');
        if (newline)
        {
            *newline = '\0';
        }
        printf("Received: %s\n", str);
        // Load f1 from the loaded library
        fcn = dlsym(lib, str);
        if (fcn == NULL)
        {
            printf("Function not found\n");
            continue;
        }

        response = fcn();

        sprintf(response_str, "%d", response);
        write(fd_write, response_str, strlen(response_str) + 1);
    }

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