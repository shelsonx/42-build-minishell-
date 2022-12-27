#include "../../includes/minishell.h"

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

int main(void)
{
    t_token token;
    t_tokenizer tokenizer;

    tokenizer.content = ft_strdup("ls -l echo ola | pwd > file << >> () ");
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
        ft_printf("type= |%d| name= |%s| value= |%s| \n", 
            token.type, get_name_token(token.type), token.value);
        free(token.value);
        free(tokenizer.characteres);
        tokenizer.characteres = ft_strdup("");
    }
    free(tokenizer.characteres);
    free(tokenizer.content);
    return (0);
}
