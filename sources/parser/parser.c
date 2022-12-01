#include "../../includes/minishell.h"

void    error(void)
{
    ft_printf("Invalid syntax\n");
    exit(1);
}

void    consume(t_parser *parser)
{
    if (parser->current_token->type == parser->token_type)
    {
        free(parser->tokenizer->characteres);
        parser->tokenizer->characteres = ft_strdup("");
        *parser->current_token = next_token(parser->tokenizer);
    }
    else
        error();
}

t_token cmd_name(t_parser *parser)
{
    t_token current_token;

    current_token = *parser->current_token;
    parser->token_type = TK_IDENTIFIER;
    consume(parser);
    return (current_token);
}

t_token redirection_op(t_parser *parser)
{
    t_token current_token;

    current_token = *parser->current_token;
    if (current_token.type == TK_GREAT)
        parser->token_type = TK_GREAT;
    else if (current_token.type == TK_LESS)
        parser->token_type = TK_LESS;
    consume(parser);
    return (current_token);
}

t_token redirection(t_parser *parser)
{
    t_token current_token;
    char    *tokens;

    tokens = ft_strdup("");
    current_token = redirection_op(parser);
    tokens = ft_strjoin(tokens, current_token.value);
    current_token = cmd_name(parser);
    tokens = ft_strjoin(tokens, " ");
    tokens = ft_strjoin(tokens, current_token.value);
    ht_insert(parser->table_redirection, ft_itoa(0), tokens);
    return (current_token);
}

t_token simple_command(t_parser *parser)
{
    t_token current_token;
    char    *tokens;

    tokens = ft_strdup("");
    current_token = cmd_name(parser);
    tokens = ft_strjoin(tokens, current_token.value);
    while (parser->current_token->type == TK_IDENTIFIER)
    {
        current_token = cmd_name(parser);
        tokens = ft_strjoin(tokens, " ");
        tokens = ft_strjoin(tokens, current_token.value);
    }
    if (parser->current_token->type == TK_GREAT || 
        parser->current_token->type == TK_LESS)
            redirection(parser);
    ht_insert(parser->table, ft_itoa(parser->index), tokens);
    parser->index++;
    return (current_token);
}

t_token pipe_sequence(t_parser *parser)
{
    t_token current_token;

    current_token = simple_command(parser);
    while (parser->current_token->type == TK_PIPE)
    {
        parser->token_type = TK_PIPE;
        consume(parser);
        current_token = simple_command(parser);
    }
    return (current_token);
}

void    parser(t_parser *parser)
{
    *parser->current_token = next_token(parser->tokenizer);
    pipe_sequence(parser);
    if (parser->current_token->type != TK_IDENTIFIER && parser->current_token->type != TK_EOF)
        error();
}
