#include "../../includes/minishell.h"

char	**get_paths_cmds(char *env_path)
{
	char	*sub_path;
	char	**paths;

	sub_path = ft_substr(env_path, 5, ft_strlen(env_path));
	paths = ft_split(sub_path, ':');
	free(sub_path);
	return (paths);
}

char	*join_path_command(char *path, char *command)
{
	char	*full_path;
	char	*path_tmp;

	path_tmp = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_tmp, command);
	free(path_tmp);
	return (full_path);
}

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

pid_t	execute_child_process(int dest, int src, char **args, int **fds)
{
	pid_t pid = create_child_process();

	if (pid == 0)
	{
		dup2(dest, src);
		ft_close_fds(fds);
		if (execve(args[0], args, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	return (pid);
}

int execute(char *line)
{
    char    **pipeline;
	int	**fds;
    pid_t child_pid;
	int status;

    pipeline = ft_split(line, ' ');
    char **args1 = create_args(pipeline, 0, 1);
	char **args2 = create_args(pipeline, 2, 3);

	fds = create_pipes(1);
	if (pipe(fds[0]) < 0) 
		perror("minishell");
	
	child_pid = execute_child_process(fds[0][1], STDOUT_FILENO, args1, fds);
	child_pid = execute_child_process(fds[0][0], STDIN_FILENO, args2, fds);
        
	ft_close_fds(fds);
    waitpid(child_pid, &status, 0);
	ft_free_tab(pipeline);
	ft_free_fds(fds);
    ft_printf("Fim!\n");
    return (0);
}
