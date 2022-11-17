# include <fcntl.h>
#include "../libs/libft/libft.h"

enum boolean {FALSE, TRUE};

enum TOKENS 
    {
        TK_IDENTIFIER,
        TK_NUMBER,
        TK_OPERATOR,
        TK_PONCTUATION,
        TK_ASSIGN
    };

typedef struct token 
{
    int     type;
    int     pos;
    char    *value;
} Token;

//variable
int pos;

int is_operator(char c)
{
    return c == '>' || c == '<' || c == '=' || c == '!';
}

int is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

char    next_char(char *content, int pos)
{
    return content[pos++];
}

void    back(int pos)
{
    pos--;
}

int is_EOF(int pos, char *content) 
{
    return pos == ft_strlen(content);
}

Token next_token(char *content)
{
    Token       token;
    nt_initial(&token);   

    while (TRUE)
    {
        current_char = content[pos++];
        switch(state)
        {
            case 0:
                if (ft_isalpha(current_char))
                {
                    term[ft_strlen(term)] = current_char;
                    term[ft_strlen(term)] = '\0';
                    state = 1;
                }
                else if (ft_isdigit(current_char))
                {
                    term[ft_strlen(term)] = current_char;
                    term[ft_strlen(term)] = '\0';
                    state = 3;
                }
                else if (is_space(current_char))
                    state = 0;
                else if (is_operator(current_char))
                {
                    term[ft_strlen(term)] = current_char;
                    term[ft_strlen(term)] = '\0';
                    state = 5;
                }
                else
                    token.type = -1;
                    token.pos = pos;
                break ;
            case 1:
                if (ft_isalpha(current_char) || ft_isdigit(current_char))
                {
                    term[ft_strlen(term)] = current_char;
                    term[ft_strlen(term)] = '\0';
                    state = 1;
                }
                else if (is_space(current_char) || is_operator(current_char))
                    state = 2;
                else
                    token.type = -1;
                    token.pos = pos;
                break;
            case 2:
                token.type = TK_IDENTIFIER;
                token.value = ft_strdup(term);
                token.pos = pos;
                free(term);
                pos--;
                return token;
            case 3:
                if (ft_isdigit(current_char))
                {
                    term[ft_strlen(term)] = current_char;
                    term[ft_strlen(term)] = '\0';
                    state = 3;
                }
                else if (!ft_isalpha(current_char))
                    state = 4;
                else
                    token.type = -1;
                    token.pos = pos;
                break;
            case 4:
                token.type = TK_NUMBER;
                token.value = ft_strdup(term);
                token.pos = pos;
                free(term);
                pos--;
                return token;
            case 5:
                token.type = TK_OPERATOR;
                token.value = ft_strdup(term);
                token.pos = pos;
                free(term);
                return token;
            }
    }
   // return token;
}

int main(void)
{
    char *line= " = abc123  123";
    Token token;
    size_t i = 0;
    while (i < ft_strlen(line))
    {
        token = next_token(line);
        ft_printf("type= |%d| value= |%s|\n", token.type, token.value);
        i++;
    }
    return (0);
}
