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

int count_occurrences(const char *s, const char *old)
{
    int     i;
    int     count;
    int     old_len;

    i = 0;
    count = 0;
    old_len = strlen(old);
    while (s[i])
    {
        if (ft_strnstr(&s[i], old, ft_strlen(s)) == &s[i])
        {
            count++;
            i += old_len - 1;
        }
        i++;
    }
    return (count);
}

char    *replace_str(const char *s, const char *old, const char *new)
{
    char    *result;
    int     i;
    int     new_len;
    int     old_len;

    new_len = ft_strlen(new);
    old_len = ft_strlen(old);
    result = malloc(ft_strlen(s) + 
        count_occurrences(s, old) * (new_len - old_len) + 1);
    i = 0;
    while (*s)
    {
        if (ft_strnstr(s, old, ft_strlen(s)) == s)
        {
            ft_strcpy(&result[i], (char *) new);
            i += new_len;
            s += old_len;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    return result;
}

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
		replaced = replace_str(*str, joinned, env);
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
			parameter = concat_strs(parameter, sub, " ");
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
			parameters = concat_strs(parameters, get_parameter(args, x, y), " ");
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
