#include "../../includes/minishell.h"

int	count_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	ft_echo(char **args)
{
	int	nb_type;
	int	i;

	i = 1;
	nb_type = 0;
	if (count_args(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			nb_type = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i][0] != '\0' && args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (nb_type == 0)
		write(1, "\n", 1);
	return (0);
}