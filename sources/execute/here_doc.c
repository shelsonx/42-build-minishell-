#include "../../includes/minishell.h"

static int	is_limiter(char *line, char *limiter)
{
	return (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& (ft_strlen(line) -1) == ft_strlen(limiter));
}

void	here_doc(int **fd, char *limiter)
{
	char	*line;
	int		fd2;

	fd2 = dup(0);
	while (true)
	{
		ft_printf("> ");
		line = ft_get_next_line(fd2);
		if (is_limiter(line, limiter))
		{
			free(line);
			close(fd2);
			close(fd[0][1]);
			break ;
		}
		write(fd[0][1], line, ft_strlen(line));
		free(line);
	}
}
