#include "../../includes/minishell.h"

static int contains_simple_quotes(char **args)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\'' || args[i][ft_strlen(args[i])-1] == '\'')
			count++;
	}
	if (count > 0)
		return (true);
	return (false);
}

void    expand_variable(char **args, t_builtin_vars *builtin_vars)
{
	int		i;
	char	*path;
	 if (contains_simple_quotes(args))
	 	return ;
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

int expand_simple_quotes(char **args)
{
	int		i;
    int     count_quotes;
	char	*path;

	i = 0;
    count_quotes = 0;
    while (args[i])
	{
        if (args[i][0] == '\'')
            count_quotes++;
		if (args[i][ft_strlen(args[i])-1] == '\'')
			count_quotes++;
        i++;
    }
    if (count_quotes == 1)
        return (false);
    i = 0;
	while (args[i])
	{
		if (args[i][0] == '\'')
		{
			path = ft_substr(args[i], 1, ft_strlen(args[i]));
			args[i] = ft_strdup(path);
			free(path);
		}
        if (args[i][ft_strlen(args[i])-1] == '\'')
		{
			path = ft_substr(args[i], 0, ft_strlen(args[i])-1);
			args[i] = ft_strdup(path);
			free(path);
		}
		i++;
	}
    return (true);
}

int expand_double_quotes(char **args, t_builtin_vars *builtin_vars)
{
	int		i;
    int     count_quotes;
	char	*path;

	i = 0;
    count_quotes = 0;
    while (args[i])
	{
        if (args[i][0] == '\"')
            count_quotes++;
		if (args[i][ft_strlen(args[i])-1] == '\"')
			count_quotes++;
        i++;
    }
    if (count_quotes == 1)
        return (false);
    i = 0;
	while (args[i])
	{
		if (args[i][0] == '\"')
		{
			path = ft_substr(args[i], 1, ft_strlen(args[i]));
			args[i] = ft_strdup(path);
			free(path);
			if (args[i][0] == '$')
				expand_variable(args, builtin_vars);
		}
        if (args[i][ft_strlen(args[i])-1] == '\"')
		{
			path = ft_substr(args[i], 0, ft_strlen(args[i])-1);
			args[i] = ft_strdup(path);
			free(path);
			if (args[i][0] == '$')
				expand_variable(args, builtin_vars);
		}
		i++;
	}
    return (true);
}
