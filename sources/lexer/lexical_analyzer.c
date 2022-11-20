#include "../../includes/minishell.h"

char    *get_name_token(int type_token)
{
    if (type_token == TK_WORD)
        return "WORD";
    if (type_token == TK_DIGIT)
        return "DIGIT";
    if (type_token == TK_QUOTE)
        return "QUOTE";
    if (type_token == TK_PARENTHESIS)
        return "PARENTHESIS";
    if (type_token == TK_OPERATOR)
        return "OPERATOR";
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

void nt_initial(t_tokenizer *tokenizer) {
    tokenizer->state = 0;
    tokenizer->len = 0;
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

void nt_case0(t_tokenizer *tokenizer)
{
    if (ft_isalpha(tokenizer->current_char))
        tokenizer->state = 1;
    else if (ft_isdigit(tokenizer->current_char))
        tokenizer->state = 3;
    else if (ft_isspace(tokenizer->current_char))
        tokenizer->state = 0;
    else if (ft_isoperator(tokenizer->current_char))
    {
        set_term(tokenizer);
        tokenizer->state = 5;
    }
    else
        tokenizer->token.type = -1;
}

void nt_case1(t_tokenizer *tokenizer)
    {
        if (ft_isalpha(tokenizer->current_char))
            {
                set_term(tokenizer);
                tokenizer->state = 1;
            }
            else if (ft_isspace(tokenizer->current_char))
                tokenizer->state = 2;
            else
            {
               tokenizer->token.type = -1;
               set_term(tokenizer);
               tokenizer->token.value = ft_strdup(tokenizer->term);
               free(tokenizer->term);
               tokenizer->state = -1;
            }
    }

 void nt_case2(t_tokenizer *tokenizer)
{
    tokenizer->token.type = TK_WORD;
    tokenizer->token.value = ft_strdup(tokenizer->term);
    free(tokenizer->term);
}

void nt_case3(t_tokenizer *tokenizer)
{
    if (ft_isdigit(tokenizer->current_char))
        {
            set_term(tokenizer);
            tokenizer->state = 3;
        }
        else if (!ft_isalpha(tokenizer->current_char))
            tokenizer->state = 4;
        else
        {
            tokenizer->token.type = -1;
        }
}

void nt_case4(size_t *pos, t_tokenizer *tokenizer)
{
    tokenizer->token.type = TK_DIGIT;
    tokenizer->token.value = ft_strdup(tokenizer->term);
    free(tokenizer->term);
    (*pos)--;
}

void nt_case5(t_tokenizer *tokenizer)
    {
        tokenizer->token.type = TK_OPERATOR;
        tokenizer->token.value = ft_strdup(tokenizer->term);
        free(tokenizer->term);
    }

t_token next_token(char *content)
{
    t_tokenizer       tokenizer;

    nt_initial(&tokenizer);
    static size_t pos;

    while (true)
    {
        tokenizer.current_char = content[pos++];
            if (is_eof(&pos, content))
            {
                free(tokenizer.term);
                exit(0);
            }

            if (tokenizer.state == 0) 
                nt_case0(&tokenizer);
            if (tokenizer.state == 1) 
                nt_case1(&tokenizer);
            if (tokenizer.state == 2) 
            {
                nt_case2(&tokenizer);
                return tokenizer.token;
            }
            if (tokenizer.state == 3) 
                nt_case3(&tokenizer);
            if (tokenizer.state == 4) 
            {
                nt_case4(&pos, &tokenizer);
                return tokenizer.token;
            }
            if (tokenizer.state == 5) 
            {
                nt_case5(&tokenizer);
                return tokenizer.token;
            }
            if (tokenizer.state == -1)
                return (tokenizer.token);
    }
}

int main(void)
{

    char *line= "abc 123 = - 12 x#yz 911";
    t_token token;

    size_t i = 0;
    while (i < ft_strlen(line))
    {
        token = next_token(line);
        if (token.type == -1)
        {
            ft_printf("Malformed word: %s\n", token.value);
            free(token.value);
            return -1;
        }
        ft_printf("type= |%d| name= |%s| value= |%s| \n", 
            token.type, get_name_token(token.type), token.value);
        free(token.value);
        i++;
    }
    return (0);
}
