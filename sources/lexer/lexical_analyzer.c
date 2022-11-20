#include "../../includes/minishell.h"

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
            {
                tokenizer->state = 1;
            }
            else if (ft_isdigit(tokenizer->current_char))
            {
                tokenizer->state = 3;
            }
            else if (ft_isspace(tokenizer->current_char))
                tokenizer->state = 0;
            else if (ft_isoperator(tokenizer->current_char))
            {
                set_term(tokenizer);
                tokenizer->state = 5;
            }
            else
            {
                tokenizer->token.type = -1;
            }
    }

void nt_case1(t_tokenizer *tokenizer)
    {
        if (ft_isalpha(tokenizer->current_char))
            {
                set_term(tokenizer);
                tokenizer->state = 1;
            }
            else if (ft_isspace(tokenizer->current_char) || ft_isoperator(tokenizer->current_char))
                tokenizer->state = 2;
            else
            {
                ft_printf("Malformed Identifier: %c\n", tokenizer->current_char);
                exit(1);
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
    }
}

int main(void)
{

    char *line= "abc 123 = - 12 xyz 911";
    t_token token;

    size_t i = 0;
    while (i < ft_strlen(line))
    {
        token = next_token(line);
        ft_printf("type= |%d| value= |%s| \n", token.type, token.value);
        free(token.value);
        i++;
    }
    return (0);
}
