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

void	fffree(void ***mem)
{
	int	i = -1;
	while (mem[++i])
		ffree(mem[i]);
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
//	printf("%i", str[i]);
	printf("\n");
}

void	ddintplay(int **str)
{
	int	i = -1;
	while (str[++i])
		dintplay(str[i]);
	printf("\n");
}

void	dddintplay(int ***str)
{
	int	i = -1;
	while (str[++i])
		ddintplay(str[i]);
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

int	*convert_to_ints(char *input)
{
	int	i, j, *rt;

	rt = malloc(sizeof(int) * (amount_of_nb(input)+1));
	i = j = 0;
	while (input[i]) {
		if (input[i] >= '0' && input[i] <= '9')
			rt[j++] = atoi(&input[i]);
		while (input[i] >= '0' && input[i] <= '9')
			i++;
		while (input[i] && (input[i] < '0' || input[i] > '9'))
			i++;
	}
	rt[j] = INT_MIN;
	return (rt);
}

long	*convert_to_longs(char *input)
{
	int	i, j;
	long	*rt;

	rt = malloc(sizeof(long) * (amount_of_nb(input)+1));
	i = j = 0;
	while (input[i]) {
		if (input[i] >= '0' && input[i] <= '9')
			rt[j++] = atol(&input[i]);
		while (input[i] >= '0' && input[i] <= '9')
			i++;
		while (input[i] && (input[i] < '0' || input[i] > '9'))
			i++;
	}
	rt[j] = LONG_MIN;
	return (rt);
}

long	**convert_to_llongs(char **input)
{
	int	i, j, k;
	long	**rt;
	
	i = 0;
	while (input[i])
		i++;
	rt = malloc(sizeof(long *)*(i+1));
	rt[i] = NULL;
	while (--i>-1)
		rt[i] = convert_to_longs(input[i]);
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

int	GCD(int a, int b)
{
	while (a != b) {
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return (a);
}

int	nb_of_digits(long nb)
{
	if (nb < 0)
		return (nb_of_digits(-nb));
	if (nb < 10)
		return (1);
	return (1 + nb_of_digits(nb/10));
}

long	power(int nb, int p)
{
	long	rt;

	rt = nb;
	if (p < 0)
		return (0);
	if (!p)
		return (1);
	while (--p)
		rt *= nb;
	return (rt);
}

//Code of the day
int	***list_machines(char **input)
{
	int	i, j, ***rt;

	j = 0;
	i = -1;
	while (input[++i])
		if (input[i][0] == 'P')
			j++;
	rt = malloc(sizeof(int **) * (j+1));
	j = 0;
	i = -1;
	while (input[++i])
		if (input[i][0] == 'P')
			rt[j++] = malloc(sizeof(int *) * 4);
	rt[j] = NULL;
	i = -1;
	while (rt[++i]) {
		j = -1;
		while (++j < 3)
			rt[i][j] = convert_to_ints(input[i*4+j]);
		rt[i][j] = NULL;
	}
	return (rt);
}

int	token_amount(int **machine)
{
	int	i, j, rt;

	rt = INT_MAX;
	i = -1;
	while (++i < 101) {
		j = -1;
		while (++j < 101)
			if (i*machine[0][0] + j*machine[1][0] == machine[2][0] && i*machine[0][1] + j*machine[1][1] == machine[2][1])
				rt = min(rt, 3*i + j);
	}
	if (rt == INT_MAX)
		return (0);
	return (rt);
}

int	main()
{
	char	**input;
	int	i, rt, ***machines_list;

	input = get_input("inputP");
	machines_list = list_machines(input);
	ffree((void **)input);
	rt = 0;
	i = -1;
	while (machines_list[++i])
		rt += token_amount(machines_list[i]);
	fffree((void ***)machines_list);
	printf("%i\n", rt);
}
