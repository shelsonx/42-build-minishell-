#include "../../includes/minishell.h"
#include <fcntl.h>

char **create_args(char **pipeline, int pos_cmd, int pos_param)
{
	char **args = malloc(sizeof (char**) * 1);
	*args = malloc(sizeof (char*) * 3);
	args[0] = get_exec_command(pipeline[pos_cmd]);
	args[1] = pipeline[pos_param];
	args[2] = NULL;

	return args;
}

pid_t	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

pid_t	execute_child_process(t_data *data)
{
	pid_t pid = create_child_process();

	if (pid == 0)
	{
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		ft_close_fds(data->fds);
		if (execve(data->args[0], data->args, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	return (pid);
}

void	exec_first_command(t_data *data, int fd_in)
{
	pid_t	child_pid;
	int		status;

	data->fd_in = fd_in;
	data->fd_out = data->fds[0][1];
	data->args = create_args(data->pipeline, 0, 1);
	child_pid = execute_child_process(data);
    waitpid(child_pid, &status, 0);
}

void	exec_middles_commands(t_data *data, int total_cmds_middles)
{
	int		i;
	int     pos_cmd;

	i = 0;
	pos_cmd = 2;
	while (i < total_cmds_middles)
	{ 
		data->fd_in = data->fds[i][0];
		data->fd_out = data->fds[i+1][1];
		data->args = create_args(data->pipeline, pos_cmd, pos_cmd + 1);
		execute_child_process(data);
		i++;
		pos_cmd += 2;
	}
}

void	exec_last_command(t_data *data, int index, int fd_out, int pos_cmd, int pos_param)
{
	pid_t	child_pid;
	int		status;

	data->fd_in = data->fds[index][0];
	data->fd_out = fd_out;
	data->args = create_args(data->pipeline, pos_cmd, pos_param);
	child_pid = execute_child_process(data);
	ft_close_fds(data->fds);
    waitpid(child_pid, &status, 0);
}

void	exec_one_command(t_data *data, int fd_in, int fd_out)
{
	pid_t	child_pid;
	int		status;

	data->fds = create_pipes(1);
	data->fd_in = fd_in;
	data->fd_out = fd_out;
	data->args = create_args(data->pipeline, 0, 1);
	child_pid = execute_child_process(data);
	ft_close_fds(data->fds);
	waitpid(child_pid, &status, 0);
}

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
