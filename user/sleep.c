#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int arg, char *argv[])
{
    if (arg <= 1)
    {
        fprintf(2, "usage: sleep n\n");
        exit(1);
    }
    else if (arg > 2)
    {
        fprintf(2, "ERROR: too much arguments!\nusage: sleep n\n");
        exit(1);
    }

    char *s = argv[1];
    int n = 0;
    while (*s >= '0' && *s <= '9')
        n = 10 * n + *s++ - '0';
    if (*s != 0)
    {
        fprintf(2, "ERROR: the second parameter must be a number!\n");
        exit(0);
    }
    sleep(n);
    exit(0);
}
