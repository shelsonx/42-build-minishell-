#include "../../includes/minishell.h"

void	parameter_expander(char **str, char *parameters, t_builtin_vars *builtin_vars)
{
	int		i;
	char	**splitted;
	char	*env;
	char	*replaced;
	char	*joinned;

	splitted = ft_split(parameters, ' ');
	i = -1;
	while (splitted[++i])
	{
		env = get_env_path(splitted[i], builtin_vars);
		joinned = ft_strjoin("$", splitted[i]);
		replaced = ft_replace_str(*str, joinned, env);
		free(*str);
		*str = replaced;
		free(joinned);
	}
	ft_free_tab(splitted);
}

char	*get_parameter(char **args, int *x, int *y)
{
	int start;
	char	*parameter;
	char	*sub;

	parameter = ft_strdup("");
	sub = NULL;
	start = -1;
	if (ft_isalpha(args[(*x)][(*y)]) || args[(*x)][(*y)] == '_')
	{
		start = (*y);
		(*y)++;
		if (ft_isalnum(args[(*x)][(*y)]) || args[(*x)][(*y)] == '_')
		{
			while (ft_isalnum(args[(*x)][(*y)]) || args[(*x)][(*y)] == '_')
				(*y)++;
		}
		sub = ft_substr(args[(*x)], start, (*y)-start);
		if (sub)
			parameter = ft_concat_strs(parameter, sub, " ");
	}
	return (parameter);
}

char	*get_parameters(char **args, int *x, int *y)
{
	char	*parameters;

	parameters = ft_strdup("");
	while (args[(*x)][(*y)])
	{
		if (args[(*x)][(*y)] == '$')
		{
			(*y)++;
			parameters = ft_concat_strs(parameters, get_parameter(args, x, y), " ");
			(*y)--;
		}
		(*y)++;
	}
	return (parameters);
}

void    expander(char **args, t_builtin_vars *builtin_vars)
{
	int		x;
	int		y;
	char	*parameters;

	x = 0;
	parameters = ft_strdup("");
	while (args[x])
	{
		y = 0;
		parameters = get_parameters(args, &x, &y);
		if (args[x][0] != '\'')
			parameter_expander(&args[x], parameters, builtin_vars);
		x++;
	}
	free(parameters);
}
