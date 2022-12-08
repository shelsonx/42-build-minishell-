#include "../../includes/minishell.h"

//gcc test_builtin_exit.c ../../libs/libft/libft.a 

# define INTMIN -2147483648 
# define INTMAX 2147483647

int	check_strarrlen(char **args)
{
	char **count;

	count = args;
	if (!args)
		return (0);
	while (*count)
		count++;
	return (count - args);
}

static char check_str_nb(char *arg)
{
	if (*arg == '+' || *arg == '-')
		arg++;
	while (*arg && (*arg >= '0' && *arg <= '9'))
		arg++;
	if (*arg == '\0')
		return (1);
	return (0);
}

static void	error_msg(char *arg, int status)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (status == 2)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		exit(1);
	}
}

void	ft_exit(char **args)
{
	float	value;
	int		args_len;

	args_len = check_strarrlen(args);
	if (args_len == 1)
		exit(0);
	else
	{
		if (*(args + 1) && check_str_nb(*(args + 1)) == 0)
			error_msg(*(args + 1), 2);
		else if (args_len > 2)
			error_msg("", 1);
		value = ft_atoi(*(args + 1));
		if (value < INTMIN || value > INTMAX)
			exit(0);
		exit((unsigned char)value);
	}
}

int main(int argc, char *argv[])
{	
    ft_exit(argv);
}