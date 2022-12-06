#include "../../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_echo(char **cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

int main(int argc, char *argv[])
{
    ft_echo(argv);
}
