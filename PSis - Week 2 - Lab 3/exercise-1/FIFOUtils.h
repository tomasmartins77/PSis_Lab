#ifndef FIFO_UTILS_H
#define FIFO_UTILS_H
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int read_FIFO(char *);

int write_FIFO(char *);

#endif