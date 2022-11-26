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
     if (type_token == TK_EOF)
        return "EOF";
    return NULL;
}

int main(void)
{
    t_tokenizer tokenizer;
    tokenizer.content = ft_strdup("(ls) a112 _ab_c1 | >> > < << ( a123");
    init_tokenizer(&tokenizer);
    int i = 0;
    while (i++ < 15)
        parser(&tokenizer);
    return (0);
}