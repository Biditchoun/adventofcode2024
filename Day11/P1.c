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
	printf("%i", str[i]);
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
	int	rt;

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
void	separate(long *rt, int i, long nb)
{
	int	dig, dig2;
	long	buff;

	buff = 0;
	dig = nb_of_digits(nb) / 2;
	dig2 = -1;
	while (dig - ++dig2) {
		buff += nb%10 * power(10, dig2);
		nb /= 10;
	}
	rt[i] = nb;
	rt[i+1] = buff;
}

long	*blink(long *stone_line)
{
	int	i, nb_of_nb;
	long	*rt;

	nb_of_nb = 0;
	i = -1;
	while (stone_line[++i] > LONG_MIN) {
		nb_of_nb++;
		if (!(nb_of_digits(stone_line[i])%2))
			nb_of_nb++;
	}
	rt = malloc(sizeof(long) * (nb_of_nb+1));
	rt[nb_of_nb] = LONG_MIN;
	while (--i > -1) {
		nb_of_nb--;
		if (!stone_line[i])
			rt[nb_of_nb] = 1;
		else if (nb_of_digits(stone_line[i]) % 2)
			rt[nb_of_nb] = stone_line[i] * 2024;
		else
			separate(rt, --nb_of_nb, stone_line[i]);
	}
	free(stone_line);
	return (rt);
}

int	main()
{
	char	*input;
	long	*stone_line;
	int	i;

	input = get_simple_input("input2");
	stone_line = convert_to_longs(input);
	free((void *)input);
	i = -1;
	while (++i < 25)
		stone_line = blink(stone_line);
	i = 0;
	while (stone_line[i] > LONG_MIN)
		i++;
	free(stone_line);
	printf("%i\n", i);
}
