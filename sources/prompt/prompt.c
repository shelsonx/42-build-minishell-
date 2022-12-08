#include "../../includes/minishell.h"

//-lreadline
//--suppressions=readline.supp

void    prompt()
{
    char    *line;
    t_parser parser_data;

    parser_data.current_token = malloc(sizeof(t_token));
    parser_data.tokenizer = malloc(sizeof(t_tokenizer));
    parser_data.tokenizer->content = malloc(sizeof(char *));

    while (true)
    {	
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
        line = readline("🎸MINISHELL𝄫: ");
        add_history(line);
        parser_data.tokenizer->content = ft_strdup(line);
        parser_data.index = 0;
        parser_data.index_redirect = 0;
        parser_data.table = create_table(5000);
        parser_data.table_redirection = create_table(1000);
        init_tokenizer(parser_data.tokenizer);
        parser(&parser_data);
        execute(&parser_data);
        free(parser_data.tokenizer->token.value);
        free(parser_data.tokenizer->characteres);
        free_hashtable(parser_data.table);
        free_hashtable(parser_data.table_redirection);
        free(line);
    }
}
