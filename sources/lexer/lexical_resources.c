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

void    invalid_token(t_tokenizer *tokenizer)
{
     if (tokenizer->token.type != TK_EOF && tokenizer->current_char != '\0' &&
        tokenizer->current_char != tokenizer->content[ft_strlen(tokenizer->content)-1])
    {
        tokenizer->current_char = tokenizer->content[tokenizer->pos-1];
        add_char(tokenizer);
        tokenizer->token.type = -1;
        tokenizer->token.value = ft_strdup(tokenizer->characteres);
         ft_printf("Malformed token: %c\n", tokenizer->token.value[ft_strlen(
            tokenizer->token.value
        )-1]);
        free(tokenizer->token.value);
        free(tokenizer->content);
        free(tokenizer->characteres);
        exit(1);
    }
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
    while ((ft_isalnum(tokenizer->current_char) || tokenizer->current_char == '-') &&
        (tokenizer->token.type != TK_EOF))
    {
        add_char(tokenizer);
        advance(tokenizer);
        if (tokenizer->token.type == TK_EOF)
            return ;
    }
}
