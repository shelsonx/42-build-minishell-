#include "../../includes/minishell.h"

void    error(t_parser *parser_data)
{
    if (parser_data->tokenizer->token.type != TK_ERROR)
        ft_printf("Invalid syntax\n");
    prompt(get_env(parser_data->builtin_vars));
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
        error(parser);
}

t_token cmd_word(t_parser *parser)
{
    t_token current_token;

    current_token = *parser->current_token;
    parser->token_type = TK_WORD;
    consume(parser);
    return (current_token);
}

t_token redirection_op(t_parser *parser)
{
    t_token current_token;

    current_token = *parser->current_token;
    if (current_token.type == TK_GREAT)
        parser->token_type = TK_GREAT;
    else if (current_token.type == TK_DGREAT)
        parser->token_type = TK_DGREAT;
    else if (current_token.type == TK_LESS)
        parser->token_type = TK_LESS;
    else if (current_token.type == TK_DLESS)
        parser->token_type = TK_DLESS;
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
    current_token = cmd_word(parser);
    tokens = ft_strjoin(tokens, " ");
    tokens = ft_strjoin(tokens, current_token.value);
    if (ft_strcmp(tokens, "") != 0)
    {
        tokens = ft_strjoin(tokens, " ");
        tokens = ft_strjoin(tokens, ft_itoa(parser->index));
        ht_insert(parser->table_redirection, ft_itoa(parser->index_redirect), tokens);
        parser->index_redirect++;
    }
    return (current_token);
}

t_token simple_command(t_parser *parser)
{
    t_token current_token;
    char    *tokens;

    tokens = ft_strdup("");
    while (parser->current_token->type == TK_GREAT ||
        parser->current_token->type == TK_DGREAT ||
        parser->current_token->type == TK_LESS ||
        parser->current_token->type == TK_DLESS)
            redirection(parser);
    if (parser->current_token->type == TK_WORD)
    {
        current_token = cmd_word(parser);
        tokens = ft_strjoin(tokens, current_token.value);
    }
    while (parser->current_token->type == TK_WORD)
    {
        current_token = cmd_word(parser);
        tokens = ft_strjoin(tokens, "*");
        tokens = ft_strjoin(tokens, current_token.value);
    }
    while (parser->current_token->type == TK_GREAT ||
        parser->current_token->type == TK_DGREAT ||
        parser->current_token->type == TK_LESS ||
        parser->current_token->type == TK_DLESS)
            redirection(parser);
    while (parser->current_token->type == TK_WORD)
    {
        current_token = cmd_word(parser);
        tokens = ft_strjoin(tokens, "*");
        tokens = ft_strjoin(tokens, current_token.value);
    }
    if (ft_strcmp(tokens, "") != 0)
    {
        ht_insert(parser->table, ft_itoa(parser->index), tokens);
        parser->index++;
    }
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
    if (parser->current_token->type != TK_WORD && parser->current_token->type != TK_EOF)
        error(parser);
}
