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

int get_amount_parameter_in_quotes(char **args)
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
			if (args[i][y] == '\'' && args[i][y+1] == '$')
				count++;
			y++;
		}
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

void	replace_str(char **args, int position, int start, int end)
{
	char *path;

	path = ft_substr(args[position], start, end);
	free(args[position]);
	args[position] = ft_strdup(path);
	free(path);
}

void	remove_extremities(char **args)
{
	int 	num_rows;

	num_rows = ft_len_rows_tab(args);
	if (args[1][0] == '\'')
		replace_str(args, 1, 1, ft_strlen(args[1]));
	if (args[num_rows-1][ft_strlen(args[num_rows-1]) -1] == '\'')
		replace_str(args, num_rows -1, 0, ft_strlen(args[num_rows-1]) -1);
}

/* void	(char **args)
{

} */

int expand_simple_quotes(char **args, t_builtin_vars *builtins)
{
	builtins->size = builtins->size;
	int		x;
	int		y;
	int		i;
	int		total_quotes;
	int **indexes = malloc(sizeof(int **) * get_amount_parameter_in_quotes(args) +1);
	total_quotes = get_amount_character(args, '\'');
	if (total_quotes % 2 != 0)
		return (false);
	remove_extremities(args);
	//dprintf(2, "total_quotes= %d\n", total_quotes);
    x = 1;
	i = 0;
	while (args[x])
	{
		dprintf(2, "%d %s\n", x, args[x]);
		y = 0;
		while(args[x][y])
		{
			if (total_quotes > 2)
			{
				if (args[x][y] == '$' && args[x][y-1] == '\'')
				{
					dprintf(2, "Yes!\n");
					indexes[i] = malloc(sizeof(int));
 					(*indexes[i]) = x;
					i++;
				}
			}
			/* while (args[x][y] == '\'')
				ft_memmove(args[x] +y, args[x] + (y+1), sizeof(char) * ft_strlen(args[x])); */
			y++;
		}
		x++;
	}
	x = 1;
	while (args[x])
	{
		y = 0;
		while (args[x][y])
		{
			while (args[x][y] == '\'')
				ft_memmove(args[x] +y, args[x] + (y+1), sizeof(char) * ft_strlen(args[x]));
			y++;
		}
		x++;
	}
	indexes[i] = NULL;
	i = 0;
	y = 0;
	char	*parameter;
	char	*path;
	char	*sub;
	//dprintf(2, "amount_quotes=%d\n", get_amount_character(args, '\''));
	while (indexes[i])
	{

		sub = ft_substr(args[(*indexes[i])], y+1, ft_strlen(args[(*indexes[i])]) -1);
		dprintf(2, "sub= |%s|\n", sub);
		path = get_env_path(sub, builtins);
		if (y > 0)
			parameter = concat_strs(ft_substr(args[(*indexes[i])], 0, y), path, "");
		else
		{
			parameter = ft_strdup(path);
			free(path);
		}
		free(sub);

		//char *parameter = get_parameter(args, builtins, (*indexes[i]), 0);
		//dprintf(2, "parameter= %s\n", parameter);
		free(args[(*indexes[i])]);
		args[(*indexes[i])] = parameter; 
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
