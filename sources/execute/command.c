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
