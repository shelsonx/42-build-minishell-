#include "../../includes/minishell.h"

char    *get_name_token(int type_token)
{
    if (type_token == TK_IDENTIFIER)
        return "IDENTIFIER";
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
    return NULL;
}

int main(void)
{

    char *line= "(ls) a112 _ab_c1 | >> > < << ( a123";
    t_token token;
    t_tokenizer tokenizer;
    static int pos;

    tokenizer.content = ft_strdup(line);
    init_tokenizer(&tokenizer);

    while (true)
    {
        token = next_token(&tokenizer);
        if (token.type == -1)
        {
            ft_printf("Malformed token: %s\n", token.value);
            free(token.value);
            free(tokenizer.content);
            free(tokenizer.characteres);
            return -1;
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
