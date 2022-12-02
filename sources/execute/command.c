#include "../../includes/minishell.h"

char	*get_exec_command(char *arg)
{
	char	*exec_command;
	char	**paths;
	char	*env_path;
	int		i;

	env_path = getenv("PATH");
	paths = get_paths_cmds(env_path);
	i = 0;
	while (paths[i])
	{
		exec_command = join_path_command(paths[i], arg);
		if (access(exec_command, X_OK) == 0)
		{
			ft_free_tab(paths);
			return (exec_command);
		}
		free(exec_command);
		exec_command = NULL;
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

void	error_command_msg(char **args, char *input_cmd)
{
	char	*msg;
	char	*tmp;

	if (args[0] == NULL)
	{
		tmp = ft_strjoin("minishell: ", input_cmd);
		msg = ft_strjoin(tmp, ": command not found\n");
		write(STDOUT_FILENO, msg, ft_strlen(msg));
		free(tmp);
		free(msg);
		free(input_cmd);
	}
}

void	exec_one_command(t_data *data, int fd_in, int fd_out)
{
	pid_t	child_pid;
	int		status;
	char	*input_cmd;

	data->fds = create_pipes(1);
	data->fd_in = fd_in;
	data->fd_out = fd_out;
	input_cmd = ft_strdup(data->pipeline[0]);
	data->args = create_args(data->pipeline);
	error_command_msg(data->args, input_cmd);
	child_pid = execute_child_process(data);
	ft_close_fds(data->fds);
	waitpid(child_pid, &status, 0);
}

void	exec_first_command(t_data *data, int fd_in)
{
	pid_t	child_pid;
	int		status;
	char	*input_cmd;

	data->fd_in = fd_in;
	data->fd_out = data->fds[0][1];
	input_cmd = ft_strdup(data->pipeline[0]);
	data->args = create_args(data->pipeline);
	error_command_msg(data->args, input_cmd);
	child_pid = execute_child_process(data);
    waitpid(child_pid, &status, 0);
}

void	exec_middles_commands(t_data *data, t_parser *parser_data, int total_cmds_middles)
{
	int		i;
	char	*input_cmd;

	i = 0;
	while (i < total_cmds_middles)
	{ 
		data->fd_in = data->fds[i][0];
		data->fd_out = data->fds[i+1][1];
		data->pipeline = ft_split(ht_search(parser_data->table, ft_itoa(i+1)), ' ');
		input_cmd = ft_strdup(data->pipeline[0]);
		data->args = create_args(data->pipeline);
		error_command_msg(data->args, input_cmd);
		execute_child_process(data);
		i++;
	}
}

void	exec_last_command(t_data *data, int index, int fd_out)
{
	pid_t	child_pid;
	int		status;
	char	*input_cmd;

	data->fd_in = data->fds[index][0];
	data->fd_out = fd_out;
	input_cmd = ft_strdup(data->pipeline[0]);
	data->args = create_args(data->pipeline);
	error_command_msg(data->args, input_cmd);
	child_pid = execute_child_process(data);
	ft_close_fds(data->fds);
    waitpid(child_pid, &status, 0);
}
