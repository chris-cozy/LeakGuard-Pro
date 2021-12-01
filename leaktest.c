#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	void *p1, *p2, *p3, *p4;

	p1 = malloc(1345); 	//freed on line 10
	p2 = malloc(2); 	//freed on line 13
	free(p1);

	p1 = malloc(134);	//leak!
	free(p2);

	p2 = calloc(5, 12); //should be ignored
	p3 = malloc(1);		//freed on line 19
	p4 = malloc(981);	//freed on line 18
	free (p4);
	free(p3);
	//free(p2);			//this is a leak, but your code should not detect it (you weren't supposed to shim calloc)

	printf("Hello World\n"); //should produce a 1024B leak.
}
