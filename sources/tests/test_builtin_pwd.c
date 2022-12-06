#include "../../includes/minishell.h"

# define ERROR 127
# define SUCCESS 0

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

void			ft_pwd(char **cmd)
{
	char		*current_path;
    int         ret;

	current_path = getcwd((char *)NULL, 0);
	if (!current_path)
	{
		ret = ERROR;
	}
	else
	{
		ft_putstr_fd(current_path, 1);
		free(current_path);
		ret = SUCCESS;
	}
	ft_putstr_fd("\n", 1);
	(void)cmd;
}

int main(int argc, char *argv[])
{
    ft_pwd(argv);
}
