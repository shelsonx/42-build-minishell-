#include "../../includes/minishell.h"

void expand_variable(char **args, t_builtin_vars *builtin_vars)
{
	int		i;
	char	*path;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			path = get_env_path(
				ft_substr(args[i], 
					1, ft_strlen(args[i])), 
				builtin_vars);
			free(args[i]);
			args[i] = ft_strdup(path);
			free(path);
		}
		i++;
	}
}