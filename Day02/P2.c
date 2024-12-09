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

//Code of the day
int	check_continuity(int *line)
{
	int	i, j;

	i = 0;
	j = 1;
	if (line[i] == INT_MIN + 1)
		i++;
	else if (line[j] == INT_MIN + 1)
		j++;
	if (i == j)
		j++;
	if (line[i] < line[j]) {
		while (line[j] > INT_MIN) {
			if (line[i] == INT_MIN + 1)
				i++;
			else if (line[j] == INT_MIN + 1)
				j++;
			if (i == j)
				j++;
			if (line[j] != INT_MIN && line[i] >= line[j])
				return (0);
			i++;
			if (line[j] != INT_MIN)
				j++;
		}
		return (1);
	}
	while (line[j] > INT_MIN) {
		if (line[i] == INT_MIN + 1)
			i++;
		else if (line[j] == INT_MIN + 1)
			j++;
		if (i == j)
			j++;
		if (line[j] != INT_MIN && line[i] <= line[j])
			return (0);
		i++;
		if (line[j] != INT_MIN)
			j++;
	}
	return (1);
}

int	check_big_jumps(int *line)
{
	int	i, j;

	i = 0;
	j = 1;
	while (line[j] > INT_MIN) {
		if (line[i] == INT_MIN + 1)
			i++;
		else if (line[j] == INT_MIN + 1)
			j++;
		if (i == j)
			j++;
		if (line[j] > INT_MIN && (abs(line[i] - line[j]) < 1 || abs(line[i] - line[j]) > 3))
			return (0);
		i++;
		if (line[j] != INT_MIN)
			j++;
	}
	return (1);
}

int	check_problem_dampener(int *line)
{
	int	buff, i = -1;

	while (line[++i] > INT_MIN) {
		buff = line[i];
		line[i] = INT_MIN + 1;
		if (check_continuity(line) && check_big_jumps(line))
			return (1);
		line[i] = buff;
	}
	return (0);
}

int	check_safety (int *line)
{
	if (check_continuity(line) && check_big_jumps(line))
		return (1);
	if (check_problem_dampener(line))
		return (1);
	return (0);
}

int	main()
{
	char	**input;
	int	i, rt, **intput;

	input = get_input("input2");
	intput = convert_to_ints(input);
	ffree((void **)input);
	rt = 0;
	i = -1;
	while (intput[++i])
		if (check_safety(intput[i]))
			rt++;
	printf("%i\n", rt);
	ffree((void **)intput);
}
