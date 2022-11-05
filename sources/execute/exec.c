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
    char    *exec_command;

    pipeline = ft_split(line, ' ');
    exec_command = get_exec_command(pipeline[0]);
    char *args[] = {exec_command,pipeline[1], NULL};
    ft_printf("exec_command=%s\n", exec_command);
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("pipex");
		exit(EXIT_FAILURE);
    }
    if (child_pid == 0)
        execve(args[0], args, NULL);
    waitpid(child_pid, NULL, 0);
    ft_printf("Fim!\n");
    free(exec_command);
    return (0);
}
