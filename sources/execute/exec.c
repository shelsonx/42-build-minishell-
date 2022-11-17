#include "../../includes/minishell.h"

char **create_args(char **pipeline, int pos_cmd, int pos_param)
{
	char **args = malloc(sizeof (char**) * 1);
	*args = malloc(sizeof (char*) * 3);
	args[0] = get_exec_command(pipeline[pos_cmd]);
	args[1] = pipeline[pos_param];
	args[2] = NULL;

	return args;
}

#include <fcntl.h>
int execute(char *line)
{
	t_data	data;
	int		total_commands;

    data.pipeline = ft_split(line, ' ');
	total_commands = ft_len_rows_tab(data.pipeline) /2;
	if (total_commands == 1)
	{
		//int fd_infile = open("infile", O_RDONLY, 0777);
		//int fd_outfile = open("outile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		exec_one_command(&data, STDIN_FILENO, STDOUT_FILENO);
	}
	if (total_commands == 2)
	{
		//int fd_infile = open("infile", O_RDONLY, 0777);
		data.fds = create_pipes(1);
		exec_first_command(&data, STDIN_FILENO);
		exec_last_command(&data, total_commands -2, STDOUT_FILENO,
			ft_len_rows_tab(data.pipeline) -2,
			ft_len_rows_tab(data.pipeline) -1);
	}
	else if (total_commands > 2)
	{
		//int fd_infile = open("infile", O_RDONLY, 0777);
		data.fds = create_pipes(total_commands -1);
		exec_first_command(&data, STDIN_FILENO);
		exec_middles_commands(&data, total_commands -2);
		exec_last_command(&data, total_commands -2, STDOUT_FILENO, 
			ft_len_rows_tab(data.pipeline) -2, 
			ft_len_rows_tab(data.pipeline) -1);
	}
	ft_close_fds(data.fds);
	ft_free_tab(data.pipeline);
	ft_free_fds(data.fds);
    return (0);
}
