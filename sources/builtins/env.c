#include "../../includes/minishell.h"

char	*get_env_path(char *path, t_builtin_vars *builtin)
{
	char	*env_path;
    char    *result_search;
    char    *num_str;
    char    **splitted;
	int		i;

	i = 0;
	while (i < builtin->size)
	{
        num_str = ft_itoa(i);
        result_search = ht_search(builtin->env, num_str);
        splitted = ft_split(result_search, '=');
        if (ft_strcmp(path, splitted[0]) == 0)
        {
            env_path = ft_strdup(splitted[1]);
            ft_free_tab(splitted);
            return (env_path);
        }
        free(num_str);
		i++;
	}
    ft_free_tab(splitted);
    env_path = ft_strdup("");
	return (env_path);
}

void    init_env(t_builtin_vars *builtin_vars, char **envp)
{

    builtin_vars->env = create_table(500);
    builtin_vars->size = 0;

    char    *num_str;
    while (envp[builtin_vars->size])
    {
        num_str = ft_itoa(builtin_vars->size);
        ht_insert(builtin_vars->env, num_str, envp[builtin_vars->size]);
        free(num_str);
        builtin_vars->size++;
    }
}

void ft_env(t_builtin_vars *builtin_vars)
{
    int i = 0;
    char    *num_str;

    while (i < builtin_vars->size)
    {
        num_str = ft_itoa(i);
        printf("%s\n", ht_search(builtin_vars->env, num_str));
        free(num_str);
        i++;
    } 
}

char    **get_env(t_builtin_vars *builtin_vars)
{
    int     i;
    char    *num_str;
    char    **env;

    i = 0;
    env = malloc(sizeof (char *) * builtin_vars->size + 1);

    while (i < builtin_vars->size)
    {
        num_str = ft_itoa(i);
        env[i] = malloc(sizeof(char) * 2);
        env[i] = ht_search(builtin_vars->env, num_str);
        free(num_str);
        i++;
    }
    env[i] = NULL;
    return (env); 
}
