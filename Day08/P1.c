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
	printf("\n");
}

void	ddintplay(int **str)
{
	int	i = -1;
	while (str[++i])
		dintplay(str[i]);
	printf("\n");
}

void	longplay(long *str)
{
	int i = -1;
	while (str[++i] > LONG_MIN)
		printf("%li ", str[i]);
	printf("\n");
}

void	llongplay(long **str)
{
	int	i = -1;
	while (str[++i])
		longplay(str[i]);
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

long	**convert_to_longs(char **input)
{
	int	i, j, k;
	long	**rt;
	
	i = 0;
	while (input[i])
		i++;
	rt = malloc(sizeof(long *)*(i+1));
	rt[i] = NULL;
	while (--i>-1) {
		rt[i] = malloc(sizeof(long) * (amount_of_nb(input[i])+1));
		k = j = 0;
		while (input[i][j]) {
			if (input[i][j] >= '0' && input[i][j] <= '9')
				rt[i][k++] = atol(&input[i][j]);
			while (input[i][j] >= '0' && input[i][j] <= '9')
				j++;
			while (input[i][j] && (input[i][j] < '0' || input[i][j] > '9'))
				j++;
		}
		rt[i][k] = LONG_MIN;
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

char	**sstrdup(char **str)
{
	char	**rt;
	int	i = 0;

	while (str[i])
		i++;
	rt = malloc(sizeof(char *) * (i+1));
	rt[i] = NULL;
	while (--i > -1)
		rt[i] = strdup(str[i]);
	return (rt);
}

long	concatenate(long n1, int n2)
{
	int	buff, i;
	buff = n2;
	i = 0;
	while (buff/10 > 0) {
		buff /= 10;
		i++;
	}
	while ( i-- > -1)
		n1 *= 10;
	return (n1+n2);
}

void	replace_char(char *str, char a, char b)
{
	int	i = -1;
	while (str[++i])
		if (str[i] == a)
			str[i] = b;
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

//Code of the day
int	**find_chars(char **input, char c)
{
	int	i, j, nb_c, **rt;

	nb_c = 0;
	i = -1;
	while (input[++i]) {
		j = -1;
		while (input[i][++j])
			if (input[i][j] == c)
				nb_c++;
	}
	rt = malloc(sizeof(int *) * (nb_c+2));
	rt[nb_c+1] = NULL;
	i = -1;
	while (++i < nb_c+1) 
		rt[i] = malloc(sizeof(int) * 3);
	rt[0][0] = nb_c;
	rt[0][1] = INT_MIN;
	nb_c = 0;
	i = -1;
	while (input[++i]) {
		j = -1;
		while (input[i][++j]) {
			if (input[i][j] == c) {
				rt[++nb_c][0] = i;
				rt[nb_c][1] = j;
				rt[nb_c][2] = INT_MIN;
			}
		}
	}
	return (rt);
}

void	place_antinode_pair(char **antinodes_map, int *coord1, int* coord2)
{
	int	i, j, imax, jmax;

	imax = 0;
	while (antinodes_map[imax])
		imax++;
	jmax = 0;
	while (antinodes_map[0][jmax])
		jmax++;
	if (coord1[0] < coord2[0])
		i = coord1[0] - abs(coord1[0] - coord2[0]);
	else
		i = coord1[0] + abs(coord1[0] - coord2[0]);
	if (coord1[1] < coord2[1])
		j = coord1[1] - abs(coord1[1] - coord2[1]);
	else
		j = coord1[1] + abs(coord1[1] - coord2[1]);
	if (i > -1 && j > -1)
		antinodes_map[i][j] = '#';
	if (coord2[0] < coord1[0])
		i = coord2[0] - abs(coord1[0] - coord2[0]);
	else
		i = coord2[0] + abs(coord1[0] - coord2[0]);
	if (coord2[1] < coord1[1])
		j = coord2[1] - abs(coord1[1] - coord2[1]);
	else
		j = coord2[1] + abs(coord1[1] - coord2[1]);
	if (i < imax && j < jmax)
		antinodes_map[i][j] = '#';
}

void	mark_antinodes(char **input, char **antinodes_map)
{
	int	i, j, k, **char_coord;
	char	chars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	i = -1;
	while (chars[++i]) {
		char_coord = find_chars(input, chars[i]);
		if (char_coord[0][0] > 1) {
			j = 0;
			while (char_coord[++j+1]) {
				k = j;
				while (char_coord[++k])
					place_antinode_pair(antinodes_map, char_coord[j], char_coord[k]);
			}
		}
		ffree((void **)char_coord);
	}
}

int	main()
{
	char	**input, **antinodes_map;
	int	rt, i, j;

	input = get_input("input2");
	antinodes_map = sstrdup(input);
	mark_antinodes(input, antinodes_map);
	//ddisplay(antinodes_map);
	ffree((void **)input);
	rt = 0;
	i = -1;
	while (antinodes_map[++i]) {
		j = -1;
		while (antinodes_map[i][++j])
			if (antinodes_map[i][j] == '#')
				rt++;
	}
	//ffree((void **)antinodes_map);
	printf("%i\n", rt);
}
