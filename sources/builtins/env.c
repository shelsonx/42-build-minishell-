#include "../../includes/minishell.h"
/*
compile:
    cc test_env.c ../utils/ht_functions.c ../utils/ht_utils.c ../utils/linkedlist_utils.c ../../libs/libft/libft.a 
*/

char	*get_env_path(char *path, t_builtin_vars *builtin)
{
	char	*env_path;
    char    *result_search;
    char    *num_str;
    char    *value;
	int		i;

	i = 0;
	while (i < builtin->size)
	{
        num_str = ft_itoa(i);
        result_search = ht_search(builtin->env, num_str);
		env_path = ft_strnstr(result_search, path, ft_strlen(result_search));
		if (env_path)
        {
            free(num_str);
            value = ft_substr(env_path, ft_strlen(path)+1, ft_strlen(env_path));
            result_search = ft_strjoin(value, "\n");
            free(value);
			return (result_search);
        }
        free(num_str);
		i++;
	}
    env_path = ft_strdup("\n");
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
