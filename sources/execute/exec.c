#include "../../includes/minishell.h"

char **create_args(char **pipeline)
{
    char	*old_pos;

    old_pos = pipeline[0];
    pipeline[0] = get_exec_command(pipeline[0]);
    free(old_pos);
	return (pipeline);
}

int	get_fd_in(t_parser *parser_data)
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
		i++;
	}
	return (STDIN_FILENO);
}

int	get_fd_out(t_parser *parser_data)
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
			return (file_fd);
		}
		i++;
	}
	return (STDOUT_FILENO);
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

int execute(t_parser *parser_data)
{
	t_data	data;
	int		total_commands;
    
	total_commands = parser_data->index;
	//only create files and return without execute nothing command.
	/* int i = 0;
	while (i < parser_data->index_redirect)
	{
		char *s = ht_search(parser_data->table_redirection, ft_itoa(i));
		dprintf(2, "%s\n", s);
		i++;
	} */
	if (total_commands == 0)
	{
		get_fd_out(parser_data);
		get_fd_in(parser_data);
		return -1;
	}
	data.pipeline = get_pipeline(&data, parser_data);
	if (total_commands == 1)
	{
		if (ht_search(parser_data->table_redirection, ft_itoa(0)) == NULL)
			exec_one_command(&data, STDIN_FILENO, STDOUT_FILENO);
		else
			exec_one_command(&data, get_fd_in(parser_data), get_fd_out(parser_data));
	}
	if (total_commands == 2)
	{
		data.fds = create_pipes(1);
		if (ht_search(parser_data->table_redirection, ft_itoa(0)) == NULL)
			exec_first_command(&data, STDIN_FILENO);
		else
			exec_first_command(&data, get_fd_in(parser_data));
		data.pipeline = ft_split(ht_search(parser_data->table, ft_itoa(1)), ' ');
		if (ht_search(parser_data->table_redirection, ft_itoa(0)) == NULL)
			exec_last_command(&data, total_commands -2, STDOUT_FILENO);
		else
			exec_last_command(&data, total_commands -2, get_fd_out(parser_data));
	}
	else if (total_commands > 2)
	{
		data.fds = create_pipes(total_commands -1);
		if (ht_search(parser_data->table_redirection, ft_itoa(0)) == NULL)
			exec_first_command(&data, STDIN_FILENO);
		else
			exec_first_command(&data, get_fd_in(parser_data));
		exec_middles_commands(&data, parser_data, total_commands -2);
		data.pipeline = ft_split(ht_search(parser_data->table, ft_itoa(total_commands -1)), ' ');
		if (ht_search(parser_data->table_redirection, ft_itoa(0)) == NULL)
			exec_last_command(&data, total_commands -2, STDOUT_FILENO);
		else
			exec_last_command(&data, total_commands -2, get_fd_out(parser_data));
	}
	exit_program(&data);
    return (0);
}
