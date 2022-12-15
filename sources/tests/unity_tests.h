#ifndef UNITY_TESTS
#define UNITY_TESTS
#include "../../includes/minishell.h"

typedef struct builtin_vars
{
    int         size;
    t_hashtable   *env;
}   t_builtin_vars;

//env
int func(void);
char	*get_env_path(char *path, t_builtin_vars *builtin);
void    init_env(t_builtin_vars *builtins, char **env);

//lexer
char    *get_name_token(int type_token);
void test_lexer(void);

///aux
char    *get_join_lines(char *filename);
#endif