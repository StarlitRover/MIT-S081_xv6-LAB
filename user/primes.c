#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
	int buff[34], p[2], size = 34;
	for (int i = 0; i < 34; ++i)
		buff[i] = i + 2;
	pipe(p);
	write(p[1], buff, size * sizeof(int));
	close(p[1]);

	while(size)
	{
		if (fork() == 0)
		{
			read(p[0], buff, size * sizeof(int));
			close(p[0]);
			pipe(p);
			printf("prime %d\n", buff[0]);
			int cnt = 0, prime = buff[0];
			for (int i = 0; i < size; ++i)
				if (buff[i] % prime != 0)
					buff[cnt++] = buff[i];
			size = cnt;
			write(p[1], buff, cnt * sizeof(int));
			close(p[1]);
		}
		else
		{
			wait(0);
			exit(0);
		}
	}
	exit(0);
}