//open
#include <fcntl.h>
//read, close
#include <unistd.h>
//printf
#include <stdio.h>
//malloc, atoi
#include <stdlib.h>
//strncpy
#include <string.h>
//INT_MIN & INT_MAX
#include <limits.h>

//utilities
void	ffree(void **mem)
{
	int	i = -1;
	printf("%p\n", mem[0]);
	while (mem[++i]) {
		printf("here ");
		free(mem[i]);}
	free(mem[i]);
	free(mem);
}

int	main()
{
	int	i, **test, **sep1, **sep2;
	test = malloc(sizeof(int *)*8);
	test[7] = NULL;
	i = -1;
	while (test[++i])
		test[i] = malloc(sizeof(int)*3);
	sep1 = test;
	sep2 = &test[4];
	
	ffree((void **)test);
	ffree((void **)sep2);
}
