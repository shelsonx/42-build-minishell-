#include "../../includes/minishell.h"

char check_str_nb(char *declar)
{
	if (*declar == '+' || *declar == '-')
		declar++;
	while (*declar && (*declar >= '0' && *declar <= '9'))
		declar++;
	if (*declar == '\0')
		return (1);
	return (0);
}

int	check_len(char **declar)
{
	char **len;

	len = declar;
	if (!declar)
		return (0);
	while (*len)
		len++;
	return (len - declar);
}

void	error_msg(char *declar, int status)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (status == 2)
	{
		ft_putstr_fd(declar, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		exit(1);
	}
}

void	ft_exit(char **declar)
{
	float	value;
	int		declar_len;

	declar_len = check_len(declar);
	if (declar_len == 1)
		exit(0);
	else
	{
		if (*(declar + 1) && check_str_nb(*(declar + 1)) == 0)
			error_msg(*(declar + 1), 2);
		else if (declar_len > 2)
			error_msg("", 1);
		value = ft_atoi(*(declar + 1));
		if (value < MININT || value > MAXINT)
			exit(0);
		exit((unsigned char)value);
	}
}
