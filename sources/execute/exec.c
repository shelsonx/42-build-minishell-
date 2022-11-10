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
		dup2(data->fd_dest, data->fd_src);
		ft_close_fds(data->fds);
		if (execve(data->args[0], data->args, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	return (pid);
}

int execute(char *line)
{
	t_data	data;
    pid_t	child_pid;
	int 	status;

    data.pipeline = ft_split(line, ' ');

	data.fds = create_pipes(1);
	if (pipe(data.fds[0]) < 0)
		perror("minishell");
	
	data.fd_dest = data.fds[0][1];
	data.fd_src = STDOUT_FILENO;
	data.args = create_args(data.pipeline, 0, 1);
	child_pid = execute_child_process(&data);

	data.fd_dest = data.fds[0][0];
	data.fd_src = STDIN_FILENO;
	data.args = create_args(data.pipeline, 2, 3);
	child_pid = execute_child_process(&data);

	ft_close_fds(data.fds);
    waitpid(child_pid, &status, 0);
	ft_free_tab(data.pipeline);
	ft_free_fds(data.fds);
    ft_printf("End!\n");
    return (0);
}
