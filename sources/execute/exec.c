#include "../../includes/minishell.h"

char **create_args(char **pipeline)
{
    char	*old_pos;

    old_pos = pipeline[0];
    pipeline[0] = get_exec_command(pipeline[0]);
    free(old_pos);
	return (pipeline);
}

void	create_fd_out(t_parser *parser_data)
{
	char	**redirection;
	char	*search;
	int 	file_fd;
	int		i;

	i = 0;
	while (i < parser_data->index_redirect)
	{
		search = ht_search(parser_data->table_redirection, ft_itoa(i));
		redirection = ft_split(search, ' ');
		if (strcmp(redirection[0], ">") == 0)
		{
			file_fd = open(redirection[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (file_fd < 0)
				perror("minishell");
		}
		if (strcmp(redirection[0], ">>") == 0)
		{
			file_fd = open(redirection[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (file_fd < 0)
				perror("minishell");
		}
		i++;
	}
}

char	**get_pipeline(t_data *data, t_parser *parser_data)
{
	data->pipeline = ft_split(ht_search(parser_data->table, ft_itoa(0)), ' ');
	return data->pipeline;
}

int	exists_commands(t_data *data)
{
	return (ft_strcmp(data->pipeline[0], "") != 0);
}

int	new_get_fd_in(t_parser *parser_data, char *index_cmd)
{
	char	**redirection;
	char	*tmp;
	char	*search;
	int 	file_fd;
	int		i;

	i = 0;
	while (i < parser_data->index_redirect)
	{
		search = ht_search(parser_data->table_redirection, ft_itoa(i));
		redirection = ft_split(search, ' ');
		if (ft_strcmp(redirection[2], index_cmd) == 0)
		{
			if (strcmp(redirection[0], "<") == 0)
			{
				file_fd = open(redirection[1], O_RDONLY);
				if (file_fd < 0)
				{
					tmp = ft_strjoin("minishell: ", redirection[1]);
					perror(tmp);
					free(tmp);
				}
				return (file_fd);
			}
		}
		i++;
	}
	return (-1);
}

int	new_get_fd_out(t_parser *parser_data, char *index_cmd)
{
	char	**redirection;
	char	*search;
	int 	file_fd;
	int		i;

	i = 0;
	while (i < parser_data->index_redirect)
	{
		search = ht_search(parser_data->table_redirection, ft_itoa(i));
		redirection = ft_split(search, ' ');
		if (ft_strcmp(redirection[2], index_cmd) == 0)
		{
			if (strcmp(redirection[0], ">") == 0)
			{
				file_fd = open(redirection[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (file_fd < 0)
					perror("minishell");
				return (file_fd);
			}
			if (strcmp(redirection[0], ">>") == 0)
			{
				file_fd = open(redirection[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
				if (file_fd < 0)
					perror("minishell");
				return (file_fd);
			}
		}
		i++;
	}
	return (-1);
}
int execute(t_parser *parser_data)
{
	t_data	data;
	int		total_commands;
    
	total_commands = parser_data->index;
	if (total_commands == 0)
	{
		create_fd_out(parser_data);
		return -1;
	}
	data.pipeline = get_pipeline(&data, parser_data);
	if (total_commands == 1)
		exec_one_command(&data, new_get_fd_in(parser_data, ft_itoa(0)), 
			new_get_fd_out(parser_data, ft_itoa(0)));
	if (total_commands == 2)
	{
		data.fds = create_pipes(1);
		exec_first_command(&data, 
			new_get_fd_in(parser_data, ft_itoa(0)),
			new_get_fd_out(parser_data, ft_itoa(0)));
		data.pipeline = ft_split(ht_search(parser_data->table, ft_itoa(1)), ' ');
		int fd_in = new_get_fd_in(parser_data, ft_itoa(1));
		if (fd_in == -1)
			fd_in = data.fds[0][0];
		exec_last_command(&data, fd_in, new_get_fd_out(parser_data, ft_itoa(1)));
	}
	else if (total_commands > 2)
	{
		data.fds = create_pipes(total_commands -1);
		exec_first_command(&data, 
			new_get_fd_in(parser_data, ft_itoa(0)),
			new_get_fd_out(parser_data, ft_itoa(0)));
		exec_middles_commands(&data, parser_data, total_commands -2);
		data.pipeline = ft_split(ht_search(parser_data->table, ft_itoa(total_commands -1)), ' ');
		int fd_in = new_get_fd_in(parser_data, ft_itoa(total_commands -1));
		if (fd_in == -1)
			fd_in = data.fds[total_commands -2][0];
		exec_last_command(&data, fd_in, new_get_fd_out(parser_data, ft_itoa(total_commands -1)));
	}
	exit_program(&data);
    return (0);
}
