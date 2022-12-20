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
		//dprintf(1, "%s\n", args[i]);
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

int	**get_indexes_parameters(char **args)
{
	int	i;
	int	y;
	int x;
	int	**indexes;

	indexes = malloc(sizeof(int **) * get_amount_character(args, '$') +1);
	i = 0;
	x = 0;
	while (args[i])
	{
		y = 0;
		while (args[i][y])
		{
			if (args[i][y] == '$')
			{
				indexes[x] = malloc(sizeof(int));
				(*indexes[x]) = y;
				x++;
			}
			y++;
		}
		i++;
	}
	indexes[x] = NULL;
	return (indexes);
}

char	*get_parameters(char **args, t_builtin_vars *builtin_vars, int i, int y, int **indexes)
{
	char	*path;
	char 	*sub;
	//int 	**indexes;
	char	*parameters;

	parameters = ft_strdup("");
	//indexes = get_indexes_parameters(args);
	if (y > 0)
		sub = ft_substr(args[i], y+1, (*indexes[0]) +1);
	else
		sub = ft_substr(args[i], y+1, (*indexes[1]) -1);
	path = get_env_path(sub, builtin_vars);
	if (y > 0)
		parameters = concat_strs(ft_substr(args[i], 0, y), path, "");
	else
		parameters = ft_strdup(path);

	char *sub2 = ft_substr(args[i], (*indexes[1]) +1, ft_strlen(args[i])-1);
	char *path2 = get_env_path(sub2, 
		builtin_vars);
	parameters = concat_strs(parameters, path2, "");

	return (parameters);
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

void    expand_variable(char **args, t_builtin_vars *builtin_vars)
{
	int		i;
	int		y;
	char	*parameters;
	char	*path;
	char 	*sub;
	int		amount_parameters;

	i = 0;
	parameters = ft_strdup("");
	path = ft_strdup("");
	sub = ft_strdup("");
	while (args[i])
	{
		//dprintf(2, "args[%d]= %s\n", i, args[i]);
		y = 0;
		while (args[i][y])
		{
			if (args[i][y] == '$')
			{
				amount_parameters = get_amount_character_2(args[i], '$');
				if (amount_parameters == 1)
				{
					sub = ft_substr(args[i], y+1, ft_strlen(args[i])-1);
					path = get_env_path(sub, 
						builtin_vars);
					if (y > 0)
						parameters = concat_strs(ft_substr(args[i], 0, y), path, "");
					else
						parameters = ft_strdup(path);
					//dprintf(2, "paremeter= %s\n", parameters);
					//dprintf(2, "path= %s\n", path);
				}
				else if (amount_parameters > 1)
				{
					if (y > 0)
						parameters = ft_substr(args[i], 0, y);
					char **splitted = ft_split(args[i], '$');
					int i = -1;
					while (splitted[++i])
						parameters = concat_strs(parameters, get_env_path(splitted[i], builtin_vars), "");
					
				}
				args[i] = ft_strdup(parameters);
				free(parameters);
			}
			y++;
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
