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
