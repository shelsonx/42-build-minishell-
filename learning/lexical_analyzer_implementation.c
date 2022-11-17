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
    return pos >= (ft_strlen(content) +2);
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
        if (is_EOF(pos, content))
            exit(0);
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
                {
                    ft_printf("Malformed Identifier: %c\n", current_char);
                    exit(1);
                }
                break;
            case 2:
                pos--;
                token.type = TK_IDENTIFIER;
                token.value = ft_strdup(term);
                free(term);
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
                break;
            case 4:
                token.type = TK_NUMBER;
                token.value = ft_strdup(term);
                free(term);
                pos--;
                return token;
            case 5:
                token.type = TK_OPERATOR;
                token.value = ft_strdup(term);
                free(term);
                return token;
        }
    }
    return token;
}

int main(void)
{
    char *line= " = > 12 abc$123 ";
    Token token;
    int i = 0;
    while (i < ft_strlen(line))
    {
        token = next_token(line);
        ft_printf("type= |%d| value= |%s|\n", token.type, token.value);
        i++;
    }
    return (0);
}
