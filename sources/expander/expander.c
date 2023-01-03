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

void	expanded_variavel_OFICIAL(char **str, char *parameters, t_builtin_vars *builtin_vars)
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
		dprintf(2, "env= %s\n", env);
		joinned = ft_strjoin("$", splitted[i]);
		replaced = replace_str(*str, joinned, env);
		dprintf(2, "replaced= %s\n", replaced);
		free(*str);
		*str = replaced;
		free(joinned);
	}
	ft_free_tab(splitted);
}

void    expand_variable(char **args, t_builtin_vars *builtin_vars)
{
	int		x;
	int		y;
	char	*parameters;
	builtin_vars->size = builtin_vars->size;
	//int		amount_parameters;
	int start;
	//int end;
	//char quote;
	char *sub = NULL;

	x = 0;
	parameters = ft_strdup("");
	start = -1;
	while (args[x])
	{
		dprintf(2, "%d |%s|\n", x, args[x]);
		y = 0;
		while (args[x][y])
		{
			if (args[x][y] == '$')
			{
				y++;
				if (ft_isalpha(args[x][y]) || args[x][y] == '_')
				{
					start = y;
					y++;
					if (ft_isalnum(args[x][y]) || args[x][y] == '_')
					{
						while (ft_isalnum(args[x][y]) || args[x][y] == '_')
							y++;
					}
					sub = ft_substr(args[x], start, y-start);
					if (sub)
						parameters = concat_strs(parameters, sub, " ");
				}
				y--;
			}
			y++;
		}
		if (args[x][0] != '\'' && args[x][ft_strlen(args[x])] != '\'')
			expanded_variavel_OFICIAL(&args[x], parameters, builtin_vars);
		x++;
	}
	free(parameters);
}

int expand_simple_quotes(char **args, t_builtin_vars *builtins)
{
	builtins->size = builtins->size;
	int		x;
	int		y;
	//int		start;
	//int 	end;

	
	//dprintf(2, "total_quotes= %d\n", total_quotes);
    x = 0;
	while (args[x])
	{
		//dprintf(2, "%d |%s|\n", x, args[x]);
		y = 0;
		while(args[x][y])
		{
			/* if (args[x][y] == '\'')
			{
				start = y+1;
				dprintf(2, "start is %d\n", y);
				y++;
				while (args[x][y] != '\'')
					y++;
				dprintf(2, "end!\nStop!\n position y= %d\n", y);
				char *sub = ft_substr(args[x], start, y);
				dprintf(2, "sub= |%s|\n", sub);
				//start = y;
			} */
			y++;
		}
		x++;
	}
	/* x = 1;
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
	} */
/* 	indexes[i] = NULL;
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
	} */
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
