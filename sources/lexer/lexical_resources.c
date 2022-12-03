#include "../../includes/minishell.h"

void add_char(t_tokenizer *tokenizer)
{
    char    *old_characteres;
    char    current_char_p[2];

    old_characteres = tokenizer->characteres;
    current_char_p[0] = tokenizer->current_char;
    current_char_p[1] = '\0';
    tokenizer->characteres = ft_strjoin(tokenizer->characteres, current_char_p);
    free(old_characteres);
}

void    advance(t_tokenizer *tokenizer)
{
    tokenizer->pos++;
    if ((size_t)tokenizer->pos > ft_strlen(tokenizer->content))
        tokenizer->token.type = TK_EOF;
    else
        tokenizer->current_char = tokenizer->content[tokenizer->pos];
}

void    skip_space(t_tokenizer *tokenizer)
{
    while (ft_isspace(tokenizer->current_char) && (tokenizer->token.type != TK_EOF))
        advance(tokenizer);
}

void    identifier(t_tokenizer *tokenizer)
{
    while (tokenizer->current_char != '\0' && 
            !ft_isparenthesis(tokenizer->current_char) &&
            !ft_isgreat(tokenizer->current_char) &&
            !ft_isless(tokenizer->current_char) &&
            !ft_ispipe(tokenizer->current_char) &&
            !ft_isspace(tokenizer->current_char) &&
            (tokenizer->token.type != TK_EOF))
    {
        add_char(tokenizer);
        advance(tokenizer);
        if (tokenizer->token.type == TK_EOF)
            return ;
    }
}
