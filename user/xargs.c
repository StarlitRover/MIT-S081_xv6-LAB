#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAXLEN 512

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(2, "usage: xargs command.\n");
		exit(1);
	}

	char buf[MAXLEN], *para[MAXARG];
	int flag = 1;

	for (int i = 1; i < argc; ++i)
		para[i - 1] = argv[i];

	while (flag)
	{
		int cnt = argc - 1, len = 0;
		while ((flag = read(0, buf + len, 1)))
		{
			if (buf[len] == '\n' || buf[len] == ' ')
			{
				if (len)
				{
					para[cnt] = (char *)malloc(len + 1);
					memmove(para[cnt], buf, len);
					para[cnt][len] = 0;
					len = 0;
					if (++cnt > MAXARG)
					{
						printf("xargs: too many arguments!\n");
						exit(1);
					}
				}

				if (buf[len] == '\n')
					break;
			}
			else if (len + 1 > MAXLEN)
			{
				printf("xargs: argument too long!\n");
				exit(1);
			}
			else
				++len;
		}
		if (!fork())
		{
			exec(para[0], para);
			exit(1);
		}
		else
			wait(0);
	}
	exit(0);
}
