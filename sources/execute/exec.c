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

int execute(char *line)
{
	t_data	data;
    pid_t	child_pid;
	int 	status;

    data.pipeline = ft_split(line, ' ');
	//ft_printf("size args=%d\n", ft_len_rows_tab(data.pipeline));
	data.fds = create_pipes(3);
	if (pipe(data.fds[0]) < 0)
		perror("minishell");
	
	if (pipe(data.fds[1]) < 0)
		perror("minishell");
	//ls -l grep x
	data.fd_in = STDIN_FILENO;
	data.fd_out = data.fds[0][1];
	data.args = create_args(data.pipeline, 0, 1);
	child_pid = execute_child_process(&data);

	data.fd_in = data.fds[0][0];
	data.fd_out = data.fds[1][1];
	data.args = create_args(data.pipeline, 2, 3);
	child_pid = execute_child_process(&data);

	data.fd_in = data.fds[1][0];
	data.fd_out = data.fds[2][1];
	data.args = create_args(data.pipeline, 4, 5);
	child_pid = execute_child_process(&data);

	data.fd_in = data.fds[2][0];
	data.fd_out = STDOUT_FILENO;
	data.args = create_args(data.pipeline, 6, 7);
	child_pid = execute_child_process(&data);

	ft_close_fds(data.fds);
    waitpid(child_pid, &status, 0);
	ft_free_tab(data.pipeline);
	ft_free_fds(data.fds);
    ft_printf("End!\n");
    return (0);
}
