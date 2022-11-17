# include "../libs/libft/libft.h"

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
    int         type; //ok
    size_t      pos;
    int         loc;
    char        *value; //ok
    char        current_char;
    int         state;
    int         len;
    char        *term;
    //Token       token;
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

void nt_initial(Token *token) {
    token->state = 0;
    token->pos = 0;
    token->len = 0;
    token->term = ft_strdup("");
    token->type = -1;
}

void nt_case0(Token *token)
    {
        if (ft_isalpha(token->current_char))
            {
                token->term[ft_strlen(token->term)] = token->current_char;
                token->term[ft_strlen(token->term)] = '\0';
                token->state = 1;
            }
            else if (ft_isdigit(token->current_char))
            {
                token->term[ft_strlen(token->term)] = token->current_char;
                token->term[ft_strlen(token->term)] = '\0';
                token->state = 3;
            }
            else if (is_space(token->current_char))
                token->state = 0;
            else if (is_operator(token->current_char))
            {
                token->term[ft_strlen(token->term)] = token->current_char;
                token->term[ft_strlen(token->term)] = '\0';
                token->state = 5;
            }
            else
            {
                token->type = -1;
                token->pos = pos;
            }
    }

void nt_case1(Token *token)
    {
        if (ft_isalpha(token->current_char) || ft_isdigit(token->current_char))
            {
                token->term[ft_strlen(token->term)] = token->current_char;
                token->term[ft_strlen(token->term)] = '\0';
                token->state = 1;
            }
            else if (is_space(token->current_char) || is_operator(token->current_char))
                token->state = 2;
            else
            {
                token->type = -1;
                token->pos = pos;
            }
    }

 void nt_case2(Token *token)
    {
        token->type = TK_IDENTIFIER;
        token->value = ft_strdup(token->term);
        token->pos = pos;
        free(token->term);
        pos--;
    }

void nt_case3(Token *token)
    {
        if (ft_isdigit(token->current_char))
            {
                token->term[ft_strlen(token->term)] = token->current_char;
                token->term[ft_strlen(token->term)] = '\0';
                token->state = 3;
            }
            else if (!ft_isalpha(token->current_char))
                token->state = 4;
            else
            {
                token->type = -1;
                token->pos = pos;
            }
    }

void nt_case4(Token *token)
    {
        token->type = TK_NUMBER;
        token->value = ft_strdup(token->term);
        token->pos = pos;
        free(token->term);
        pos--;   
    }

void nt_case5(Token *token)
    {
        token->type = TK_OPERATOR;
        token->value = ft_strdup(token->term);
        token->pos = pos;
        free(token->term);
    }

Token next_token(char *content)
{
    Token       token;
    nt_initial(&token);   

    while (TRUE)
    {
        token.current_char = content[pos++];
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
                nt_case4(&token);
                return token;
            }
            if (token.state == 5) 
            {
                nt_case5(&token);
                return token;
            }
    }
   // return token;
}

int main(void)
{

    char *line= " = abc123 123 ";
    Token token;
    size_t i = 0;
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