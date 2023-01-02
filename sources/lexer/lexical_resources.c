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

int is_quote_cloded(t_tokenizer *tokenizer, char quote)
{
    while (tokenizer->current_char != quote)
    {
        if (tokenizer->current_char == '\0' || tokenizer->token.type == TK_EOF)
            return (false);
        add_char(tokenizer);
        advance(tokenizer);
    }
    return (true);
}

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

int check_quotes(t_tokenizer *tokenizer)
{
    char    quote;
    int     closed;
    if (is_quote(tokenizer->current_char))
    {
        quote = tokenizer->current_char;
        add_char(tokenizer);
        advance(tokenizer);
        closed = is_quote_cloded(tokenizer, quote);
        if (!closed)
        {
            ft_putendl_fd("Unclosed quotes!", 2);
            tokenizer->token.type = TK_ERROR;
            return (true);
        }
        add_char(tokenizer);
        advance(tokenizer);
        return (true);
    }
    return (false);
}

void    tk_word(t_tokenizer *tokenizer)
{
    while (!ft_strchr(METACHARS, tokenizer->current_char))
    {
        if (check_quotes(tokenizer))
            return ;
        add_char(tokenizer);
        advance(tokenizer);
        if (tokenizer->token.type == TK_EOF)
            return ;
    }
}
