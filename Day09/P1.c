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

long	**convert_to_llongs(char **input)
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

//Code of the day
int	*convert_to_ints(char *input)
{
	int	*rt, i;

	rt = malloc(sizeof(int) * (strlen(input)+1));
	i = -1;
	while (input[++i] && input[i] != '\n')
		rt[i] = input[i] - '0';
	rt[i] = INT_MIN;
	return (rt);
}

int	*spread_intput(int *intput)
{
	int	i, j, *rt;

	j = 0;
	i = -1;
	while (intput[++i] > INT_MIN)
		j += intput[i];
	rt = malloc(sizeof(int) * (j+1));

	i = j = -1;
	while (intput[++i] > INT_MIN) {
		while (intput[i]--) {
			if ( !(i%2) )
				rt[++j] = i/2;
			else
				rt[++j] = -1;
		}
	}
	rt[++j] = INT_MIN;
	return (rt);
}

void	compact_line(int *line)
{
	int	i, j;

	j = 0;
	while (line[j] > INT_MIN)
		j++;
	i = -1;
	while (++i < j) {
		while (line[j] < 0 && i < j)
			j--;
		if (line[i] == -1) {
			line[i] = line[j];
			line[j] = -1;
		}
	}
}

int	main()
{
	char	*input;
	int	*spread_line, *intput, i;
	long	rt;

	input = get_simple_input("input2");
	intput = convert_to_ints(input);
	free(input);
	spread_line = spread_intput(intput);
	free(intput);
	compact_line(spread_line);
	rt = 0;
	i = -1;
	while (spread_line[++i] > -1)
		rt += i * spread_line[i];
	free(spread_line);
	printf("%li\n", rt);
}
