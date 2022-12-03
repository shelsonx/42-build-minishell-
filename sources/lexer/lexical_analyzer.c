#include "../../includes/minishell.h"

void init_tokenizer(t_tokenizer *tokenizer) {
    tokenizer->pos = 0;
    tokenizer->current_char = tokenizer->content[tokenizer->pos];
    tokenizer->characteres = ft_strdup("");
    tokenizer->token.type = -1;
}

t_token get_next_token(t_tokenizer *tokenizer)
{
    tokenizer->token.value = ft_strdup(tokenizer->characteres);
    advance(tokenizer);
    return (tokenizer->token);
}

t_token next_token(t_tokenizer *tokenizer)
{
    while (tokenizer->token.type != TK_EOF)
    {   
        if (ft_isspace(tokenizer->current_char))
            skip_space(tokenizer);
        if (ft_isparenthesis(tokenizer->current_char))
            return get_parenthesis(tokenizer);
        if (ft_isgreat(tokenizer->current_char))
            return get_great(tokenizer);
        if (ft_isless(tokenizer->current_char))
            return get_less(tokenizer);
        if (ft_ispipe(tokenizer->current_char))
            return get_pipe(tokenizer);
        if (tokenizer->current_char != '\0')
            return get_word(tokenizer);
        advance(tokenizer);
    }
    return tokenizer->token;
}
