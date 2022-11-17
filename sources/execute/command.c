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
