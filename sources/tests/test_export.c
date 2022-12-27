#include "../../includes/minishell.h"

// cc ../builtins/env.c test_export.c ../utils/ht_functions.c ../utils/ht_utils.c ../utils/linkedlist_utils.c ../../libs/libft/libft.a 

int is_valid_identifier(char *key);
int check_if_is_equal(char *key);

void print_export(t_builtin_vars *builtins)
{
	int i = 0;
    char *num_str;
    char **splitter_env;
    char *key;
    char *value;

     while (i < builtins->size)
    {
        num_str = ft_itoa(i);
        splitter_env = ft_split(ht_search(builtins->env, num_str), '=');
        key = splitter_env[0];
        value = splitter_env[1];

        if (!value)
        {
        if(check_if_is_equal(ht_search(builtins->env, num_str)))
            printf("declare -x %s\"\"\n", ht_search(builtins->env, num_str));
        else
            printf("declare -x %s\n", ht_search(builtins->env, num_str));
        }
        else
		    printf("declare -x %s=\"%s\"\n", key, value);
        free(num_str);
        i++;
    } 
}

void insert_args_in_ht(t_builtin_vars *builtins, char *key, char *value)
{   
	ht_insert(builtins->env, key, value);
    builtins->size++;
}

void delete_args_in_ht(t_builtin_vars *builtins, char *key)
{   
	ht_delete(builtins->env, key);
    builtins->size--;
}

int key_exists(t_builtin_vars *builtins, char *args)
{
    char **splitted_args; 
    char *num_str;
    int i;

    i = 0;
    while(i < builtins->size)
    {   
        num_str = ft_itoa(i);
        
        if(check_if_is_equal(args))
        {
            splitted_args = ft_split(args, '=');

            if(ft_strncmp(args, ht_search(builtins->env, num_str), ft_strlen(splitted_args[0])) == 0)
                return TRUE;

        } else{
            if(ft_strcmp(args, ht_search(builtins->env, num_str)) == 0)
                return TRUE;
        }
        i++;
    }
    return FALSE;
}

int is_equal_values(t_builtin_vars *builtins, char *args)
{
    char **splitted_args; 
    char **splitted_ht_search; 
    char *num_str;
    char *search;
    int i;

    i = 0;
    num_str = ft_strdup("");
    while(i < builtins->size)
    {
        num_str = ft_itoa(i);
        search = ht_search(builtins->env, num_str);
        splitted_args = ft_split(args, '=');
        splitted_ht_search = ft_split(search, '=');
        if(ft_strcmp(splitted_args[0], splitted_ht_search[0]) == 0 &&  
            ft_strcmp(splitted_args[1], splitted_ht_search[1]) != 0)
            return TRUE;
        i++;
    }
    return FALSE;
}

int get_position_env(t_builtin_vars *builtins, char *args)
{   
    char *num_str;
    char *search;
    char    **splitted;
    int i;

    i = 0;
    while(i < builtins->size)
    {
        num_str = ft_itoa(i);
        search = ht_search(builtins->env, num_str);
        if (check_if_is_equal(args))
        {
            splitted = ft_split(args, '=');
            if (ft_strncmp(search, args, ft_strlen(splitted[0])) == 0)
                return (i);
        }
        i++;
    }
    return -1;
}

void insert_args_in_export(t_builtin_vars *builtins, char *args)
{
    char *num_str;

    num_str = ft_itoa(builtins->size);
    insert_args_in_ht(builtins, num_str, args);
}


char	ft_isunderscore(char c)
{
	if (c == '_')
		return (true);
	else
		return (false);
}

int is_valid_identifier(char *args)
{
        if (!ft_isunderscore(args[0]) && !ft_isalpha(args[0]))
    {
        printf("minishell: export: `%s': not a valid identifier\n", args);
        return (FALSE);
    } else {
        int i = 0;
        while(args[i])
        {
            if (!ft_isunderscore(args[i]) && !ft_isalnum(args[i]))
            {
              printf("minishell: export: `%s': not a valid identifier\n", args);
              return (FALSE);  
            }
            i++;    
        }
    }
    return (TRUE);
}

int check_if_is_equal(char *args) {
    int i = 0 ;
        while(args[i])
        {
            if(args[i] == '=')
                {
                    return TRUE;
                }
            i++;
        }
        return FALSE;
    }

void ft_export_aux(t_builtin_vars *builtins, char **args)
{
    int i = 1;
    char **splitter_equals;

    while(args[i])
    {
        if (is_equal_values(builtins, args[i]))
        {
            int position = get_position_env(builtins, args[i]);
            delete_args_in_ht(builtins, ft_itoa(position));
            insert_args_in_ht(builtins, ft_itoa(position), args[i]);
        }
        else
        {
            if(!check_if_is_equal(args[i]))
            {
                if(is_valid_identifier(args[i]))
                    insert_args_in_export(builtins, args[i]);
            }
            else
            {
                splitter_equals = ft_split(args[i], '=');
                if(ft_strlen(args[i]) > 1)
                {
                    if(is_valid_identifier(splitter_equals[0]))
                        insert_args_in_export(builtins, args[i]);
                }
                else
                {
                    if(is_valid_identifier(args[i]))
                        insert_args_in_export(builtins, args[i]);
                }
            }
        }
        i++; 
    }
}


int main(int argc, char **argv, char **envp)
{
	t_builtin_vars builtins;
    init_env(&builtins, envp);

    ft_export_aux(&builtins, argv);
    //ft_env(&builtins);
    // delete_args_in_ht(&builtins, ft_itoa(builtins.size--)); 
    // (builtins.size)--; 
    // delete_args_in_ht(&builtins, ft_itoa(builtins.size--));
    // (builtins.size)--; 
    print_export(&builtins);
}

//
//set_env = exist_key