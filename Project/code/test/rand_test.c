#include <stdio.h>
#include <stdlib.h>

#define RAND_MAX 1

int main(int argc, char const *argv[])
{
	for(int i; i<10; i++)
	{
		printf("%d\n", rand());
	}
	return 0;
}