#include "../../includes/minishell.h"

int	count_declar(char **declar)
{
	int	size;

	size = 0;
	while (declar[size])
		size++;
	return (size);
}

int	ft_echo(char **declar)
{
	int	type;
	int	i;

	i = 1;
	type = FALSE;
	if (count_declar(declar) > 1)
	{
		while (declar[i] && ft_strcmp(declar[i], "-n") == 0)
		{
			type = TRUE;
			i++;
		}
		while (declar[i])
		{
			ft_putstr_fd(declar[i], 1);
			if (declar[i][0] != '\0' && declar[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (type == FALSE)
		write(1, "\n", 1);
	return (0);
}