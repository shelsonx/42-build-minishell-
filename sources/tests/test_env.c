#include "../../includes/minishell.h"
/*
compile:
    cc test_env.c ../utils/ht_functions.c ../utils/ht_utils.c ../utils/linkedlist_utils.c ../../libs/libft/libft.a 
*/

typedef struct s_builtins
{
    int         size;
    HashTable   *env;
}   t_builtins;

char	*get_env_path(char *path, t_builtins *builtin)
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

int main(int argc, char **argv, char **envp)
{
    t_builtins builtins;

    builtins.env = create_table(2000);
    builtins.size = 0;

    char    *num_str;
    while (envp[builtins.size])
    {
        num_str = ft_itoa(builtins.size);
        ht_insert(builtins.env, num_str, envp[builtins.size]);
        free(num_str);
        builtins.size++;
    }

    printf("size env= %d\n", builtins.size);
    int i = 0;
    while (i < builtins.size)
    {
        num_str = ft_itoa(i);
        printf("%s\n", ht_search(builtins.env, num_str));
        free(num_str);
        i++;
    }
    
    char *var = "SHELL";
    printf("*************************************************\n");
    printf("TEST GET_ENV |%s|\n", var);
    printf("*************************************************\n");
    
    char *result;
    result = get_env_path(var, &builtins);
    printf("%s", result);
    free(result);
    free_hashtable(builtins.env);

    return (0);
}
