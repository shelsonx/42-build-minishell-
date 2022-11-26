#include "../../includes/minishell.h"

void    error(void)
{
    ft_printf("Invalid syntax");
    return ;
}

void    consume(t_tokenizer *tokenizer, t_token *current_token, int token_type)
{
    if (current_token->type == token_type)
        *current_token = next_token(tokenizer);
    else
        error();
}

void    parser(t_tokenizer *tokenizer)
{
    t_token current_token;
    current_token = next_token(tokenizer);
    ft_printf("%s\n", get_name_token(current_token.type));
    free(current_token.value);
}
