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
    char        current_char;
    int         state = 0;
    int static  pos = 0;
    int         len = 0;
    char        *term = ft_strdup("");
    Token       token;
    token.type = -1;

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
    return token;
}

int main(void)
{
    char *line= " = abc123  123";
    Token token;
    int i = 0;
    while (i < ft_strlen(line))
    {
        if (token.pos >= ft_strlen(line))
            return -1;
        token = next_token(line);
        ft_printf("type= |%d| value= |%s| pos= |%d|\n", token.type, token.value, token.pos);
        i++;
    }
    return (0);
}
