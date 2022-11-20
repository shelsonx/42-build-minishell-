#include "../../includes/minishell.h"

char    next_char(char *content, int pos)
{
    return content[pos++];
}

void    back(int pos)
{
    pos--;
}

int is_eof(size_t *pos, char *content) 
{
    return *pos == (ft_strlen(content) +2);
}

void nt_initial(t_token *token) {
    token->state = 0;
    token->len = 0;
    token->term = ft_strdup("");
    token->type = -1;
}

void set_term(t_token *token)
{
    char    *old_term;
    char    current_char_p[2];

    old_term = token->term;
    current_char_p[0] = token->current_char;
    current_char_p[1] = '\0';
    token->term = ft_strjoin(token->term, current_char_p);
    free(old_term);
}

void nt_case0(t_token *token)
    {
        if (ft_isalpha(token->current_char))
            {
                token->state = 1;
            }
            else if (ft_isdigit(token->current_char))
            {
                token->state = 3;
            }
            else if (ft_isspace(token->current_char))
                token->state = 0;
            else if (ft_isoperator(token->current_char))
            {
                set_term(token);
                token->state = 5;
            }
            else
            {
                token->type = -1;
            }
    }

void nt_case1(t_token *token)
    {
        if (ft_isalpha(token->current_char))
            {
                set_term(token);
                token->state = 1;
            }
            else if (ft_isspace(token->current_char) || ft_isoperator(token->current_char))
                token->state = 2;
            else
            {
                ft_printf("Malformed Identifier: %c\n", token->current_char);
                exit(1);
            }
    }

 void nt_case2(t_token *token)
{
    token->type = TK_WORD;
    token->value = ft_strdup(token->term);
    free(token->term);
}

void nt_case3(t_token *token)
{
    if (ft_isdigit(token->current_char))
        {
            set_term(token);
            token->state = 3;
        }
        else if (!ft_isalpha(token->current_char))
            token->state = 4;
        else
        {
            token->type = -1;
        }
}

void nt_case4(size_t *pos, t_token *token)
{
    token->type = TK_DIGIT;
    token->value = ft_strdup(token->term);
    free(token->term);
    (*pos)--;
}

void nt_case5(t_token *token)
    {
        token->type = TK_OPERATOR;
        token->value = ft_strdup(token->term);
        free(token->term);
    }

t_token next_token(char *content)
{
    t_token       token;

    nt_initial(&token);
    static size_t pos;

    while (true)
    {
        token.current_char = content[pos++];
            if (is_eof(&pos, content))
            {
                free(token.term);
                exit(0);
            }

            if (token.state == 0) 
                nt_case0(&token);
            if (token.state == 1) 
                nt_case1(&token);
            if (token.state == 2) 
            {
                nt_case2(&token);
                return token;
            }
            if (token.state == 3) 
                nt_case3(&token);
            if (token.state == 4) 
            {
                nt_case4(&pos, &token);
                return token;
            }
            if (token.state == 5) 
            {
                nt_case5(&token);
                return token;
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