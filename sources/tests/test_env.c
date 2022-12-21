#include "../../includes/minishell.h"
/*
compile:
    cc test_env.c ../utils/ht_functions.c ../utils/ht_utils.c ../utils/linkedlist_utils.c ../../libs/libft/libft.a 
*/

typedef struct builtin_vars
{
    int         size;
    t_hashtable   *env;
}   t_builtin_vars_2;

char	*get_env_path_2(char *path, t_builtin_vars_2 *builtin)
{
    builtin->size = builtin->size;
    char *PATH = ft_strdup("");
    PATH = getenv(path);
    if (PATH == NULL)
        PATH = ft_strdup("\n");
    else
        PATH = ft_strjoin(PATH, "\n");
    return (PATH);
	/* char	*env_path;
    char    *result_search;
    char    *num_str;
    char    *value;
	int		i;

	i = 0;
	while (i < builtin->size)
	{
        num_str = ft_itoa(i);
        result_search = ht_search(builtin->env, num_str);
        dprintf(2, "result_search= %s\n", result_search);
		env_path = ft_strnstr(result_search, path, ft_strlen(path));
        //dprintf(2, "env_path= %s\n\n", env_path);
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
	return (env_path); */
}

void    init_env_2(t_builtin_vars_2 *builtins, char **envp)
{

    builtins->env = create_table(500);
    builtins->size = 0;

    char    *num_str;
    while (envp[builtins->size])
    {
        num_str = ft_itoa(builtins->size);
        ht_insert(builtins->env, num_str, envp[builtins->size]);
        free(num_str);
        builtins->size++;
    }
}

int main(int argc, char **argv, char **envp)
{
   
    t_builtin_vars_2 builtins;

    init_env_2(&builtins, envp);

    /* printf("size env= %d\n", builtins.size);
    int i = 0;
    while (i < builtins.size)
    {
        num_str = ft_itoa(i);
        printf("%s\n", ht_search(builtins.env, num_str));
        free(num_str);
        i++;
    } */
    
    char *var = "U";
    printf("*************************************************\n");
    printf("TEST GET_ENV |%s|\n", var);
    printf("*************************************************\n");
    
    char *result;
    result = get_env_path_2(var, &builtins);
    printf("%s", result);
    free(result);
    free_hashtable(builtins.env);

    return (0);
}
