#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	void *p1, *p2, *p3, *p4;

	p1 = malloc(1345);
	p2 = malloc(2);
	free(p1);

	p1 = malloc(134); // leak!
	free(p2);

	p2 = calloc(5, 12); // should be ignored
	p3 = malloc(1);
	p4 = malloc(981);
	free(p4);
	free(p3);

	printf("Hello World\n"); // should produce a 1024B leak.

	return 0;
}
