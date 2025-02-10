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

int	power(int nb, int p)
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
//This was my first idea for solving the puzzle, and I am pretty sure the thinking on how it should behave is completely valid
//It basically re-uses the code from the first part, except it pre-determines the result of common numbers to make it run faster
//It's pretty ugly, but I really wanted to make it work ; alas, I have written something wrong somewhere and I can't find where
//This means I am "one off" wherever there are 40 blinks or more on some inputs
//I am still leaving this code in as a tribute to my efforts to make it work
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

long	**determine_common_cases()
{
	int	i, j, k;
	long	**rt, *buff;

	rt = malloc(sizeof(long *) * 11);
	rt[10] = NULL;
	i = -1;
	while (++i < 10)
		rt[i] = malloc(sizeof(long) * 42);
	i = -1;
	while (++i < 10) {
		buff = malloc(sizeof(long)*2);
		buff[0] = rt[i][0] = i;
		buff[1] = LONG_MIN;
		j = 0;
		while (++j < 41) {
			buff = blink(buff);
			k = 0;
			while (buff[k] > LONG_MIN)
				k++;
			rt[i][j] = k;
		}
		rt[i][j] = LONG_MIN;
		free (buff);
	}
	return (rt);
}

long	*shorten_line(long *line)
{
	long	*rt;
	int	i, j;

	i = -1;
	j = 0;
	while (line[++i] > LONG_MIN)
		if (line[i] < 0)
			j++;
	rt = malloc(sizeof(long) * (i - j + 1));
	i = j = -1;
	while (line[++i] > LONG_MIN)
		if (line[i] != -1)
			rt[++j] = line[i];
	rt[++j] = LONG_MIN;
	free (line);
	return (rt);
}

int	main()
{
	char	*input;
	int	i, j, blinks;
	long	rt, *stone_line, **common_cases;

	blinks = 40;
	input = get_simple_input("input2");
	printf("input : %s", input);
	stone_line = convert_to_longs(input);
	free((void *)input);
	common_cases = determine_common_cases();
	i = -1;
	while (++i < blinks - 40)
		stone_line = blink(stone_line);
	i = rt = 0;
	while (++i < min(40, blinks+1)) {
		j = -1;
//		longplay(stone_line);
		while (stone_line[++j] > LONG_MIN) {
			if (stone_line[j] < 10) {
				rt += common_cases[stone_line[j]][min(blinks, 40)+1-i];
//				printf("+%li ", common_cases[stone_line[j]][min(blinks, 40)+1-i]);
				stone_line[j] = -1;
			}
		}
//		printf("\n");
		stone_line = shorten_line(stone_line);
		stone_line = blink(stone_line);
	}
//	longplay(stone_line);
	ffree((void **)common_cases);
	i = -1;
	while (stone_line[++i] > LONG_MIN)
		rt++;
	free(stone_line);
	printf("%i blinks : %li\n", blinks, rt);
}
