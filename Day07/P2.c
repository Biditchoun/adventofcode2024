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

//Code of the day
//Holy shit this one is ugly
//If you want to understand what is happening, I highly recommend removing the // from the data displays I've put
char	*create_operators(long *equation, char c1)
{
	char	*rt;
	int	i = 0;
	while (equation[i] > LONG_MIN)
		i++;
	rt = malloc(--i);
	rt[--i] = 0;
	while (--i > -1)
		rt[i] = c1;
	return (rt);
}

void	move_several_c2(char *operators, char c1, char c2, int c2_at_end, int nb_op)
{
	int	i, j;

	i = nb_op;
	j = c2_at_end;
	while (j--)
		operators[--i] = c1;
	while (operators[i] == c1)
		i--;
	operators[i] = c1;
	operators[++i] = c2;
	j = c2_at_end;
	while (j--)
		operators[++i] = c2;
}

void	add_a_c2(char *operators, char c1, char c2, int c2_at_end, int nb_op)
{
	int	i;
	
	i = c2_at_end;
	while (i--)
		operators[--nb_op] = c1;
	i = -1;
	while (++i <= c2_at_end)
		operators[i] = c2;
}

void	simple_move(char *operators, char c1, char c2, int i)
{
	i--;
	while (operators[i] == c1)
		i--;
	operators[i] = c1;
	operators[i+1] = c2;
}

int	nb_c2_at_end(char *operators, char c2, int i)
{
	int	rt = 0;
	while (operators[--i] == c2)
		rt++;
	return (rt);
}

int	next_bi_operators_list(char *operators, char c1, char c2)
{
	int	i, nb_c1, nb_op, c2_at_end;

	nb_c1 = 0;
	i = -1;
	while (operators[++i])
		if (operators[i] == c1)
			nb_c1++;
	nb_op = strlen(operators);
	c2_at_end = nb_c2_at_end(operators, c2, nb_op);
	if (nb_c1) {
		if (nb_c1 == nb_op)
			operators[0] = c2;
		else if (!c2_at_end)
			simple_move(operators, c1, c2, nb_op);
		else if (c2_at_end == nb_op - nb_c1)
			add_a_c2(operators, c1, c2, c2_at_end, nb_op);
		else
			move_several_c2(operators, c1, c2, c2_at_end, nb_op);
	}
	return (nb_c1);
}

int	check_equation_result(long *equation, char *operators)
{
	long	result;
	int	i, j;

	i = -1;
	j = 1;
	result = equation[1];
	while (operators[++i]) {
		if (operators[i] == '+')
			result += equation[++j];
		else if (operators[i] == '*')
			result *= equation[++j];
		else if (operators[i] == '|')
			result = concatenate(result, equation[++j]);
	}
	if (equation[0] == result)
		return (1);
	return (0);
}

int	check_bi_operators(long *equation, char c1, char c2)
{
	char	*operators;
	long	result;
	int	rt, nb_c1;
	
	operators = create_operators(equation, c1);
	nb_c1 = 1;
	rt = 0;
	while (nb_c1) {
		rt += check_equation_result(equation, operators);
		nb_c1 = next_bi_operators_list(operators, c1, c2);
	}
	free(operators);
	return (rt);
}

void	fuse_operators(char *operators, char *buff)
{
	int	i, j;

	i = j = -1;
	while (operators[++i]) {
		while (operators[i] == '|')
			i++;
		operators[i] = buff[++j];
	}
}

int	check_tri_operators(long *equation)
{
	char	*operators, *buff;
	int	i, nb_op, nb_con, rt;

	operators = create_operators(equation, '+');
	operators[0] = '|';
	nb_con = 1;
	nb_op = strlen(operators);
	buff = create_operators(equation, '+');
	buff[nb_op - nb_con] = 0;
	rt = 0;
	if (nb_op > 2) {
		while (nb_op - nb_con > 1) {
			while (next_bi_operators_list(buff, '+', '*')) {
				fuse_operators(operators, buff);
				rt += check_equation_result(equation, operators);
//				longplay(equation);
//				printf("%s\n", operators); 
			}
			replace_char(operators, '*', '+');
			replace_char(buff, '*', '+');
			nb_con = nb_op - next_bi_operators_list(operators, '+', '|');
			buff[nb_op - nb_con] = 0;
		}
	}
	free(operators);
	free(buff);
//	printf("\n");
	return (rt);
}

int	check_equation(long *equation)
{
	int	rt;

	rt = 0;
	rt += check_bi_operators(equation, '+', '*');
	if (!rt)
		rt += check_bi_operators(equation, '+', '|');
	if (!rt)
		rt += check_bi_operators(equation, '*', '|');
	if (!rt)
		rt += check_tri_operators(equation);
	return (rt);
}

int	main()
{
	char	**input;
	long	rt, **intput;
	int	i;

	input = get_input("input2");
	intput = convert_to_longs(input);
	ffree((void **)input);
	rt = 0;
	i = -1;
	while (intput[++i])
		if (check_equation(intput[i]))
			rt += intput[i][0];
	printf("%li\n", rt);
}
