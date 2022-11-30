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
        parser->index++;
        ht_insert(parser->table, ft_itoa(parser->index), parser->current_token->value);
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

t_token simple_command(t_parser *parser)
{
    t_token current_token;
    
    current_token = cmd_name(parser);
    if (parser->current_token->type == TK_IDENTIFIER)
        current_token = cmd_name(parser);
    return (current_token);
}

t_token pipe_sequence(t_parser *parser)
{
    t_token current_token;

    current_token = simple_command(parser);
    if (parser->current_token->type == TK_PIPE)
    {
        parser->token_type = TK_PIPE;
        consume(parser);
        current_token = simple_command(parser);
    }
    return (current_token);
}

void    parser(t_parser *parser)
{
    t_token token;
    *parser->current_token = next_token(parser->tokenizer);
    ht_insert(parser->table, ft_itoa(parser->index), parser->current_token->value);
    token = pipe_sequence(parser);
    if (parser->current_token->type != TK_IDENTIFIER && parser->current_token->type != TK_EOF)
    {
        ft_printf("token_type= %d\n", parser->current_token->type);
        error();
    }
    
    /* ft_printf("%s\n", ht_search(parser->table, ft_itoa(0)));
    ft_printf("%s\n", ht_search(parser->table, ft_itoa(1))); */
    //ft_printf("current_token %s\n", get_name_token(parser->current_token->type));
}
