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

int is_eof(size_t *pos, char *content) 
{
    return *pos == (ft_strlen(content) +2);
}

void init_tokenizer(t_tokenizer *tokenizer) {
    tokenizer->pos = 0;
    tokenizer->current_char = tokenizer->content[tokenizer->pos];
    tokenizer->term = ft_strdup("");
}

void set_term(t_tokenizer *tokenizer)
{
    char    *old_term;
    char    current_char_p[2];

    old_term = tokenizer->term;
    current_char_p[0] = tokenizer->current_char;
    current_char_p[1] = '\0';
    tokenizer->term = ft_strjoin(tokenizer->term, current_char_p);
    free(old_term);
}

t_token invalid_token(t_tokenizer *tokenizer)
{
     if (tokenizer->token.type != TK_EOF && tokenizer->current_char != '\0' &&
        tokenizer->current_char != tokenizer->content[ft_strlen(tokenizer->content)-1])
    {
        set_term(tokenizer);
        tokenizer->token.type = -1;
        tokenizer->token.value = ft_strdup(tokenizer->term);
        return (tokenizer->token);
    }
}

void    advance(t_tokenizer *tokenizer)
{
    tokenizer->pos++;
    if (tokenizer->pos > ft_strlen(tokenizer->content) -1)
        tokenizer->token.type = TK_EOF;
    else
        tokenizer->current_char = tokenizer->content[tokenizer->pos];
}

void    skip_space(t_tokenizer *tokenizer)
{
    while (ft_isspace(tokenizer->current_char) && tokenizer->token.type != TK_EOF)
        advance(tokenizer);
}

void    identifier(t_tokenizer *tokenizer)
{
    while (ft_isalnum(tokenizer->current_char) || tokenizer->current_char == '_' &&
        (tokenizer->token.type != TK_EOF))
    {
        set_term(tokenizer);
        advance(tokenizer);
        if (tokenizer->token.type == TK_EOF)
            return ;
    }
}

t_token get_next_token(t_tokenizer *tokenizer)
{
    tokenizer->token.value = ft_strdup(tokenizer->term);
    advance(tokenizer);
    return (tokenizer->token);
}

t_token next_token(t_tokenizer *tokenizer)
{
    while (tokenizer->token.type != TK_EOF)
    {   
        if (ft_isspace(tokenizer->current_char))
            skip_space(tokenizer);
        
        if (ft_isalpha(tokenizer->current_char) || tokenizer->current_char == '_')
        {
            identifier(tokenizer);
            tokenizer->token.type = TK_IDENTIFIER;
            tokenizer->token.value = ft_strdup(tokenizer->term);
            return (tokenizer->token);
        }
        if (ft_isparenthesis(tokenizer->current_char))
        {
            set_term(tokenizer);
            tokenizer->token.type = TK_PARENTHESIS;
            return get_next_token(tokenizer);
        }
        if (ft_isgreat(tokenizer->current_char))
        {
            if (ft_isgreat(tokenizer->content[tokenizer->pos+1]))
            {
                tokenizer->token.type = TK_DGREAT;
                set_term(tokenizer);
                advance(tokenizer);
            }
            else
                tokenizer->token.type = TK_GREAT;
            set_term(tokenizer);
            return get_next_token(tokenizer);
        }
        if (ft_isless(tokenizer->current_char))
        {
            if (ft_isless(tokenizer->content[tokenizer->pos+1]))
            {
                tokenizer->token.type = TK_DLESS;
                set_term(tokenizer);
                advance(tokenizer);
            }
            else
                tokenizer->token.type = TK_LESS;
            set_term(tokenizer);
            return get_next_token(tokenizer);
        }
        if (ft_ispipe(tokenizer->current_char))
        {
            set_term(tokenizer);
            tokenizer->token.type = TK_PIPE;
            return get_next_token(tokenizer);
        }
        invalid_token(tokenizer);
        advance(tokenizer);

    }
     if (tokenizer->token.type == TK_EOF)
            exit(0);
    return tokenizer->token;
    
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
            //free(token.value);
            return -1;
        }
        ft_printf("type= |%d| name= |%s| value= |%s| \n", 
            token.type, get_name_token(token.type), token.value);
        free(tokenizer.term);
        tokenizer.term = ft_strdup("");
    }
    return (0);
}
