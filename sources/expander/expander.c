#include "../../includes/minishell.h"

char	*concat_strs(char *str1, char *str2, char *separator)
{
	char	*joinned;
	char	*tmp;

	tmp = ft_strjoin(str1, separator);
	joinned = ft_strjoin(tmp, str2);
	free(tmp);
	free(str1);
	free(str2);
	return (joinned);
}

int contains_quotes(char **args, int quote)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (args[++i])
	{
		if (args[i][0] == quote || args[i][ft_strlen(args[i])-1] == quote)
			count++;
	}
	if (count > 0)
		return (true);
	return (false);
}

int get_amount_character(char **args, char character)
{
	int	i;
	int	y;
	int	count;

	count = 0;
	i = 0;
	while (args[i])
	{
		y = 0;
		while (args[i][y])
		{
			if (args[i][y] == character)
				count++;
			y++;
		}
		i++;
	}
	return (count);
}

int get_amount_character_2(char *args, char character)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (args[i] == character)
			count++;
		i++;
	}
	return (count);
}

char	*get_parameter(char **args, t_builtin_vars *builtin_vars, int x, int y)
{
	char	*parameter;
	char	*path;
	char	*sub;

	sub = ft_substr(args[x], y+1, ft_strlen(args[x]) -1);
	path = get_env_path(sub, builtin_vars);
	if (y > 0)
		parameter = concat_strs(ft_substr(args[x], 0, y), path, "");
	else
	{
		parameter = ft_strdup(path);
		free(path);
	}
	free(sub);
	return (parameter);
}

char	*get_parameters(char **args, t_builtin_vars *builtin_vars, int x, int y)
{
	char	*parameters;
	char 	**key_parameters;
	int 	i;

	parameters = ft_strdup("");
	if (y > 0)
		parameters = ft_substr(args[x], 0, y);
	key_parameters = ft_split(args[x], '$');
	i = -1;
	while (key_parameters[++i])
		parameters = concat_strs(parameters, get_env_path(key_parameters[i], builtin_vars), "");
	ft_free_tab(key_parameters);
	return (parameters);
}

void    expand_variable(char **args, t_builtin_vars *builtin_vars)
{
	int		x;
	int		y;
	char	*parameters;
	int		amount_parameters;

	x = 0;
	parameters = ft_strdup("");
	while (args[x])
	{
		y = 0;
		while (args[x][y])
		{
			if (args[x][y] == '$')
			{
				amount_parameters = get_amount_character_2(args[x], '$');
				if (amount_parameters == 1)
					parameters = get_parameter(args, builtin_vars, x, y);
				else if (amount_parameters > 1)
					parameters = get_parameters(args, builtin_vars, x, y);
				free(args[x]);
				args[x] = ft_strdup(parameters);
				free(parameters);
			}
			y++;
		}
		x++;
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
