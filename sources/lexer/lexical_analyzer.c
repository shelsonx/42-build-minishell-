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
    tokenizer->content;
    tokenizer->term = ft_strdup("");
    tokenizer->token.type = -1;
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

/* void set_invalid_token(t_tokenizer *tokenizer)
{
    tokenizer->token.type = -1;
    set_term(tokenizer);
    tokenizer->token.value = ft_strdup(tokenizer->term);
    free(tokenizer->term);
    tokenizer->state = -1;
} */

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

t_token next_token(t_tokenizer *tokenizer)
{
   
    while (true)
    {
        ft_printf("current_char= |%c| pos=%d\n", tokenizer->current_char, tokenizer->pos);
        advance(tokenizer);
        if (tokenizer->token.type == TK_EOF)
            exit(0);
    }
    
}

int main(void)
{

    char *line= "_ab_c1 $a123";
    t_token token;
    t_tokenizer tokenizer;

    tokenizer.content = ft_strdup(line);
    init_tokenizer(&tokenizer);
    size_t i = 0;
    while (true)
    {
        token = next_token(&tokenizer);
        
       /*  if (token.type == -1)
        {
            ft_printf("Malformed token: %s\n", token.value);
            free(token.value);
            return -1;
        }
        ft_printf("type= |%d| name= |%s| value= |%s| \n", 
            token.type, get_name_token(token.type), token.value);
        free(token.value); */
        i++;
    }
    return (0);
}
