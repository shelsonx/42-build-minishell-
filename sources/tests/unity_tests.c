#include "unity_tests.h"
#include "../../includes/minishell.h"

//funct test to env

void    init_env(t_builtin_vars *builtins, char **env)
{

    builtins->env = create_table(500);
    builtins->size = 0;
    
    char    *num_str;
    while (env[builtins->size])
    {
        num_str = ft_itoa(builtins->size);
        ht_insert(builtins->env, num_str, env[builtins->size]);
        free(num_str);
        builtins->size++;
    }
}

/* char	*get_env_path(char *path, t_builtin_vars *builtin)
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
} */


//functions to test lexer

char    *get_name_token(int type_token)
{
    if (type_token == TK_WORD)
        return "WORD";
    if (type_token == TK_PARENTHESIS)
        return "PARENTHESIS";
    if (type_token == TK_GREAT)
        return "GREAT";
    if (type_token == TK_LESS)
        return "LESS";
    if (type_token == TK_DGREAT)
        return "DGREAT";
    if (type_token == TK_DLESS)
        return "DLESS";
    if (type_token == TK_PIPE)
        return "PIPE";
     if (type_token == TK_EOF)
        return "EOF";
    return NULL;
}

void test_lexer(void)
{
    int fd;
    t_token token;
    t_tokenizer tokenizer;

    tokenizer.content = ft_strdup("ls | echo > filename");
    init_tokenizer(&tokenizer);

    while (true)
    {
        token = next_token(&tokenizer);
        if (tokenizer.token.type == TK_EOF)
            break ;
        if (token.type == -1)
        {
            ft_printf("Malformed token: %s\n", token.value);
            free(token.value);
            free(tokenizer.content);
            free(tokenizer.characteres);
            exit(1);
        }
        fd = open("out", O_WRONLY | O_CREAT | O_APPEND, 0777);
        dup2(fd, STDERR_FILENO);
        dprintf(2, "type= |%d| name= |%s| value= |%s| \n",
            token.type, get_name_token(token.type), token.value);
        free(token.value);
        free(tokenizer.characteres);
        tokenizer.characteres = ft_strdup("");
    }
    free(tokenizer.characteres);
    free(tokenizer.content);
    close(fd);
}

char    *get_join_lines(char *filename)
{
    int file_fd;
    char *line;
    char *lines;

    line = ft_strdup("");
    lines = ft_strdup("");
    file_fd = open(filename, O_RDONLY, 0777);
    while (line = ft_get_next_line(file_fd))
        lines = ft_strjoin(lines, line);
    return lines;
}
