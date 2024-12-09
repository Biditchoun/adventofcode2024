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
	while (mem[++i])
		free(mem[i]);
	free(mem);
}

void	ddisplay(char **str)
{
	int	i = -1;
	while (str[++i])
		printf("%s\n",str[i]);
	printf("\n");
}

void	dintplay(int *str)
{
	int i = -1;
	while (str[++i] > INT_MIN)
		printf("%i ", str[i]);
	printf("%i\n", str[i]);
}

void	ddintplay(int **str)
{
	int	i = -1;
	while (str[++i])
		dintplay(str[i]);
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

int	amount_of_nb(char *str)
{
	int	rt, i = rt = 0;
	while (str[i]) {
		if (str[i] >= '0' && str[i] <= '9')
			rt++;
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		while (str[i] && (str[i] < '0' || str[i] > '9'))
			i++;
	}
	return (rt);
}

int	**convert_to_ints(char **input)
{
	int	i, j, k, **rt;
	
	i = 0;
	while (input[i])
		i++;
	rt = malloc(sizeof(int *)*(i+1));
	rt[i] = NULL;
	while (--i>-1) {
		rt[i] = malloc(sizeof(int) * (amount_of_nb(input[i]) +1));
		k = j = 0;
		while (input[i][j]) {
			if (input[i][j] >= '0' && input[i][j] <= '9')
				rt[i][k++] = atoi(&input[i][j]);
			while (input[i][j] >= '0' && input[i][j] <= '9')
				j++;
			while (input[i][j] && (input[i][j] < '0' || input[i][j] > '9'))
				j++;
		}
		rt[i][k] = INT_MIN;
	}
	return (rt);
}

char	*get_simple_input(char *filename)
{
	int	fd;
	char	buff[999999], *rt;

	fd = open(filename, O_RDONLY);
	read(fd, buff, 999998);
	close(fd);
	buff[999998] = 0;
	rt = malloc(strlen(buff)+1);
	strcpy(rt, buff);
	return (rt);
}

//Code of the day
int	check_mul(char *str)
{
	int	i, nb1, nb2;

	if (strncmp(str, "mul(", 4))
		return (0);
	i = 0;
	while (str[i] && i < 4)
		i++;
	nb1 = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != ',')
		return (0);
	i++;
	nb2 = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != ')')
		return (0);
	return (atoi(&str[nb1]) * atoi(&str[nb2]));
}

int	main()
{
	char	*input;
	int	i, rt;

	input = get_simple_input("input2");
	rt = 0;
	i = -1;
	while (input[++i])
		if (input[i] == 'm')
			rt += check_mul(&input[i]);
	free(input);
	printf("%i\n", rt);
}
