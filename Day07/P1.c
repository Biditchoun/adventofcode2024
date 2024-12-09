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

//Code of the day
char	*create_operators(long *equation)
{
	char	*rt;
	int	i = 0;
	while (equation[i] > LONG_MIN)
		i++;
	rt = malloc(--i);
	rt[--i] = 0;
	while (--i > -1)
		rt[i] = '+';
	return (rt);
}

void	move_several_muls(char *operators, int mul_at_end, int nb_op)
{
	int	i, j;

	i = nb_op;
	j = mul_at_end;
	while (j--)
		operators[--i] = '+';
	while (operators[i] == '+')
		i--;
	operators[i] = '+';
	operators[++i] = '*';
	j = mul_at_end;
	while (j--)
		operators[++i] = '*';
}

void	add_a_mul(char *operators, int mul_at_end, int nb_op)
{
	int	i;
	
	i = mul_at_end;
	while (i--)
		operators[--nb_op] = '+';
	i = -1;
	while (++i <= mul_at_end)
		operators[i] = '*';
}

void	simple_move(char *operators, int i)
{
	i--;
	while (operators[i] == '+')
		i--;
	operators[i] = '+';
	operators[i+1] = '*';
}

int	nb_mul_at_end(char *operators, int i)
{
	int	rt = 0;
	while (operators[--i] == '*')
		rt++;
	return (rt);
}

int	next_operators_list(char *operators)
{
	int	i, nb_plus, nb_op, mul_at_end;

	nb_plus = 0;
	i = -1;
	while (operators[++i])
		if (operators[i] == '+')
			nb_plus++;
	nb_op = strlen(operators);
	mul_at_end = nb_mul_at_end(operators, nb_op);
	if (nb_plus) {
		if (nb_plus == nb_op)
			operators[0] = '*';
		else if (!mul_at_end)
			simple_move(operators, nb_op);
		else if (mul_at_end == nb_op - nb_plus)
			add_a_mul(operators, mul_at_end, nb_op);
		else
			move_several_muls(operators, mul_at_end, nb_op);
	}
	return (nb_plus);
}

int	check_equation(long *equation)
{
	char	*operators;
	long	result;
	int	i, j, rt, nb_plus;
	
	operators = create_operators(equation);
	nb_plus = 1;
	rt = 0;
	while (nb_plus) {
		i = -1;
		j = 1;
		result = equation[1];
		while (operators[++i]) {
			if (operators[i] == '+')
				result += equation[++j];
			else if (operators[i] == '*')
				result *= equation[++j];
		}
		rt++;
		nb_plus = next_operators_list(operators);
	}
	free(operators);
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
