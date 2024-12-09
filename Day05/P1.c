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
int	check_update(int **rules, int *update)
{
	int	i, j, k;

	i = -1;
	while (update[++i] > INT_MIN && update[i+1] > INT_MIN) {
		j = -1;
		while (rules[++j]) {
			if (rules[j][1] == update[i]) {
				k = i;
				while (update[++k] > INT_MIN)
					if (rules[j][0] == update[k])
						return (0);
			}
		}
	}
	return (1);
}

int	get_mid_list(int *update)
{
	int	i = 0;
	while (update[i] > INT_MIN)
		i++;
	return (update[(i-1)/2]);
}

int	main()
{
	char	**input;
	int	i, j, *buff, **rules, **updates, rt;

	input = get_input("input1");
	rules = convert_to_ints(input);
	ffree((void **)input);

	i = 0;
	while (rules[i][0] > INT_MIN)
		i++;
	updates = &rules[i+1];
	buff = rules[i];
	rules[i] = NULL;

	rt = 0;
	j = -1;
	while (updates[++j])
		if (check_update(rules, updates[j]))
			rt += get_mid_list(updates[j]);
	printf("%i\n", rt);
	rules[i] = buff;
	ffree((void **)rules);
}
