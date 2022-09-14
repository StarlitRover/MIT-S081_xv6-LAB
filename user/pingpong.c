#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int arg, char *argv[])
{
    int p[2];
    pipe(p);
    char buff[5];
    if (fork() == 0)
    {
        if (read(p[0], buff, 5) != 5)
        {
            printf("Read Parent ERROR!\n");
            exit(1);
        }
        close(p[0]);
        printf("%d: received %s\n", getpid(), buff);
        write(p[1], "pong", 5);
        close(p[1]);
    }
    else
    {
        write(p[1], "ping", 5);
        close(p[1]);
        wait(0);
        if (read(p[0], buff, 5) != 5)
        {
            printf("Read Child ERROR!\n");
            exit(1);
        }
        printf("%d: received %s\n", getpid(), buff);
        close(p[0]);
    }
    exit(0);
}
