#include "stdio.h"

int main(int argc, char *argv[])
{
    char result_str[100] = "";
    int pos = 0;
    for (int i = 1; i < argc; i++)
    {
        int x = 0;
        while (argv[i][x] != '\0')
        {
            result_str[pos] = argv[i][x];
            x++;
            pos++;
        }
    }

    printf("%s\n", result_str);
}