

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t p = getpid();
	printf("Hello, I am process %d\n",p);

	if (argc > 1) {
		int iarg = atoi(argv[1]);

		for (int i=0; i < iarg; i++)
		{
			kill(getpid(), SIGCONT);
		}
		printf("sent some useless signals.\n");
	}
	return 0;
}
