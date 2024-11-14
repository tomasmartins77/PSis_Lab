#include "string.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
    char result_str[100] = "";
    for (int i = 1; i < argc; i++)
    {
        strcat(result_str, argv[i]);
    }
    printf("%s\n", result_str);
}