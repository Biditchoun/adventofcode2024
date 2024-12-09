//open
#include <fcntl.h>
//read, close
#include <unistd.h>
//printf
#include <stdio.h>
//malloc, abs
#include <stdlib.h>
//strncpy
#include <string.h>
//INT_MIN & INT_MAX
#include <limits.h>

//utilities
void	ffree(void **mem)
{
	int	i = -1;
	while (mem[++i])
		free(mem[i]);
	free(mem);
}

void	ddisplay(char **str)
{
	int	i = -1;
	while (str[++i])
		printf("%s\n",str[i]);
}

void	dintplay(int *str)
{
	int i = -1;
	while (str[++i] > INT_MIN)
		printf("%i ", str[i]);
}

void	ddintplay(int **str)
{
	int	i = -1;
	while (str[++i]) {
		dintplay(str[i]);
		printf("\n");
	}
	printf("\n");
}

char	**get_input(char *filename)
{
	int	i, j, lines, fd;
	char	buf[999999], **rt;

	fd = open(filename,O_RDONLY);
	read(fd,buf,999998);
	close (fd);
	buf[999998]=0;

	lines = 1;
	i = -1;
	while (buf[++i])
		if (buf[i] == '\n')
			lines++;
	rt = malloc(sizeof(char *)*(lines+1));
	rt[lines] = NULL;

	i = -1;
	lines = j = 0;
	while (buf[++i]) {
		if (buf[i] == '\n') {
			rt[lines] = malloc(i-j+1);
			strncpy(rt[lines], &buf[j], i-j+1);
			rt[lines][i-j] = 0;
			j = i+1;
			lines++;
		}
	}
	return (rt);
}

//code for the day
int	**convert_to_ints(char **input)
{
	int	i, j, **rt;
	
	i = 0;
	while (input[i])
		i++;
	rt = malloc(sizeof(int *)*(i+1));
	rt[i] = NULL;
	while (--i>-1) {
		rt[i] = malloc(sizeof(int)*3);
		rt[i][0] = atoi(input[i]);
		j = 0;
		while (input[i][j] >= '0' && input[i][j] <= '9')
			j++;
		rt[i][1] = atoi(&input[i][j]);
		rt[i][2] = INT_MIN;
	}
	return (rt);
}

void	sort_intput(int **intput, int pos)
{
	int	i, j, min, minj;

	i = -1;
	while (intput[++i+1]) {
		min = intput[i][pos];
		minj = i;
		j = i;
		while (intput[++j]) {
			if (min > intput[j][pos]) {
				min = intput[j][pos];
				minj = j;
			}
		}
		if (i != minj) {
			intput[minj][pos] = intput[i][pos];
			intput[i][pos] = min;
		}
	}
}

int	main()
{
	char	**input;
	int	i, rt, **intput;

	input = get_input("input2");
	intput = convert_to_ints(input);
	ffree((void **)input);
	sort_intput(intput, 0);
	sort_intput(intput, 1);

	rt = 0;
	i = -1;
	while (intput[++i])
		rt += abs(intput[i][0] - intput[i][1]);
	printf("%i\n", rt);
	ffree((void **)intput);
}
