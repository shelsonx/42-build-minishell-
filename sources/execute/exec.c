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

int execute(char *line)
{
    char    **pipeline;
    char    *exec_command1;
	char    *exec_command2;
	int	**fds;

    pipeline = ft_split(line, ' ');
    exec_command1 = get_exec_command(pipeline[0]);
	exec_command2 = get_exec_command(pipeline[2]);
    char *args1[] = {exec_command1,pipeline[1], NULL};
	char *args2[] = {exec_command2,pipeline[3], NULL};

	fds = create_pipes(1);
	if (pipe(fds[0]) < 0) 
		perror("minishell");
	
    pid_t child_pid1 = fork();
    if (child_pid1 < 0)
    {
        perror("pipex");
		exit(EXIT_FAILURE);
    }

    if (child_pid1 == 0)
	{	
		dup2(fds[0][1], STDOUT_FILENO);
		close(fds[0][0]);
		close(fds[0][1]);
		execve(args1[0], args1, NULL);
	}

	pid_t child_pid2 = fork();
	if (child_pid2 == 0)
	{	
		dup2(fds[0][0], STDIN_FILENO);
		close(fds[0][0]);
		close(fds[0][1]);
		execve(args2[0], args2, NULL);
	}
        
	close(fds[0][0]);
	close(fds[0][1]);
    waitpid(child_pid1, NULL, 0);
	waitpid(child_pid2, NULL, 0);
    ft_printf("Fim!\n");
	ft_free_fds(fds);
    free(exec_command1);
	free(exec_command2);
    return (0);
}


