#include "../../includes/minishell.h"

char **create_args(char **pipeline)
{
	int i;
	char **args = malloc(sizeof (char**) * 1);
	*args = malloc(sizeof (char*) * ft_len_rows_tab(pipeline) + 1);
	args[0] = get_exec_command(pipeline[0]);

	i = 1;
	while (i < ft_len_rows_tab(pipeline))
	{
		args[i] = pipeline[i];
		i++;
	}
	args[ft_len_rows_tab(pipeline)] = NULL;
	return args;
}

int execute(t_parser *parser_data)
{
	t_data	data;
	int		total_commands;
    
	total_commands = parser_data->index;
	data.pipeline = ft_split(ht_search(parser_data->table, ft_itoa(0)), ' ');
    
	if (total_commands == 1)
		exec_one_command(&data, STDIN_FILENO, STDOUT_FILENO);
	if (total_commands == 2)
	{
		data.fds = create_pipes(1);
		exec_first_command(&data, STDIN_FILENO);
		data.pipeline = ft_split(ht_search(parser_data->table, ft_itoa(1)), ' ');
		exec_last_command(&data, total_commands -2, STDOUT_FILENO,
			ft_len_rows_tab(data.pipeline) -2,
			ft_len_rows_tab(data.pipeline) -1);
	}
	else if (total_commands > 2)
	{
		data.fds = create_pipes(total_commands -1);
		exec_first_command(&data, STDIN_FILENO);
		exec_middles_commands(&data, parser_data, total_commands -2);
		data.pipeline = ft_split(ht_search(parser_data->table, ft_itoa(total_commands -1)), ' ');
		exec_last_command(&data, total_commands -2, STDOUT_FILENO, 
			ft_len_rows_tab(data.pipeline) -2, 
			ft_len_rows_tab(data.pipeline) -1);
	}
	exit_program(&data);
    return (0);
}
