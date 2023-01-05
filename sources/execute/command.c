#include "../../includes/minishell.h"

int	is_full_path(char *arg)
{
	int		i;
	char	**paths;
	
	paths = get_paths_cmds(getenv("PATH"));
	i = 0;
	while (paths[i])
	{
		if (ft_strncmp(paths[i], arg, ft_strlen(paths[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	get_exit_status(char *arg)
{
	char	*exec_command;
	char	**paths;
	int		i;

	paths = get_paths_cmds(getenv("PATH"));
	i = 0;
	exec_command = NULL;
	while (paths[i])
	{
		if (ft_strncmp("./", arg, 2) == 0)
			exec_command = ft_substr(arg, 2, ft_strlen(arg));
		else if (!is_full_path(arg))
			exec_command = join_path_command(paths[i], arg);
		else
			exec_command = ft_strdup(arg);
		if (access(exec_command, X_OK) == 0)
		{
			ft_free_tab(paths);
			free(exec_command);
			return (0);
		}
		i++;
	}
	if (access(exec_command, F_OK) == 0)
	{
		ft_free_tab(paths);
		return (126);
	}
	ft_free_tab(paths);
	return (127);
}

char	*get_exec_command(char *arg)
{
	char	*exec_command;
	char	**paths;
	int		i;

	paths = get_paths_cmds(getenv("PATH"));
	i = 0;
	while (paths[i])
	{
		if (ft_strncmp("./", arg, 2) == 0)
			exec_command = ft_substr(arg, 2, ft_strlen(arg));
		else if (!is_full_path(arg))
			exec_command = join_path_command(paths[i], arg);
		else
			exec_command = ft_strdup(arg);
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
	*data->exit_status = get_exit_status(input_cmd);
	data->args = create_args(data->pipeline);
	error_command_msg(data->args, input_cmd);
	if (data->args[0] == NULL)
		return ;
	child_pid = execute_child_process(data);
	ft_close_fds(data->fds);
	waitpid(child_pid, &status, 0);
}

void	exec_first_command(t_data *data, int fd_in, int fd_out)
{
	char	*input_cmd;

	data->fd_in = fd_in;
	if (fd_out == -1)
		data->fd_out = data->fds[0][1];
	else
		data->fd_out = fd_out;
	input_cmd = ft_strdup(data->pipeline[0]);
	data->args = create_args(data->pipeline);
	error_command_msg(data->args, input_cmd);
	if (data->args[0] == NULL)
		return ;
	execute_child_process(data);
}

void	exec_middles_commands(t_data *data, t_parser *parser_data, int total_cmds_middles)
{
	int		i;
	char	*input_cmd;
	int		fd_in;
	int		fd_out;

	i = 0;
	while (i < total_cmds_middles)
	{
		fd_in = new_get_fd_in(parser_data, ft_itoa(i+1)); 
		fd_out = new_get_fd_out(parser_data, ft_itoa(i+1));
		if (fd_in == -1) 
			data->fd_in = data->fds[i][0];
		else
			data->fd_in = fd_in;
		if (fd_out == -1)
			data->fd_out = data->fds[i+1][1];
		else
			data->fd_out = fd_out;
		data->pipeline = ft_split(ht_search(parser_data->table, ft_itoa(i+1)), ' ');
		input_cmd = ft_strdup(data->pipeline[0]);
		data->args = create_args(data->pipeline);
		error_command_msg(data->args, input_cmd);
		if (data->args[0] == NULL)
			return ;
		execute_child_process(data);
		i++;
	}
}

void	exec_last_command(t_data *data, int fd_in, int fd_out)
{
	char	*input_cmd;

	data->fd_in = fd_in;
	if (fd_out == -1)
		data->fd_out = STDOUT_FILENO;
	else
		data->fd_out = fd_out;
	input_cmd = ft_strdup(data->pipeline[0]);
	*data->exit_status = get_exit_status(input_cmd);
	data->args = create_args(data->pipeline);
	error_command_msg(data->args, input_cmd);
	if (data->args[0] == NULL)
		return ;
	else
		*data->exit_status = 0;
	execute_child_process(data);
}
