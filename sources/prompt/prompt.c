#include "../../includes/minishell.h"

//-lreadline
//--suppressions=readline.supp

void    prompt(char **envp)
{
    char    *line;
    char    *prompt;
    t_parser parser_data;
    t_builtin_vars builtin_vars;
    char *minishell_char = ft_strdup("\033[1;31m🎸MINISHELL𝄫:");
    char *pwd = get_env_path( "PWD", &builtin_vars);
    char *pwd_tmp = pwd;

    init_env(&builtin_vars, envp);
	parser_data.builtin_vars = &builtin_vars;
    parser_data.current_token = malloc(sizeof(t_token));
    parser_data.tokenizer = malloc(sizeof(t_tokenizer));
    parser_data.tokenizer->content = malloc(sizeof(char *));
    

    while (true)
    {	
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
        minishell_char = ft_strdup("\033[1;31m🎸MINISHELL𝄫:");
        pwd = get_env_path( "PWD", &builtin_vars);
        pwd_tmp = pwd;
        pwd = ft_strjoin("\033[1;33m", pwd);
        prompt = ft_strjoin(minishell_char, pwd);
        prompt = ft_strjoin(prompt, "$ \033[0m");
        line = readline(prompt);
        if(line == NULL) 
        {
            exit(0);
        }
        add_history(line);
        parser_data.tokenizer->content = ft_strdup(line);
        parser_data.index = 0;
        parser_data.index_redirect = 0;
        parser_data.table = create_table(5000);
        parser_data.table_redirection = create_table(1000);
        init_tokenizer(parser_data.tokenizer);
        parser(&parser_data);
        execute(&parser_data);
        free_hashtable(parser_data.table);
        free_hashtable(parser_data.table_redirection);
        free(line);
        free(minishell_char);
        free(pwd_tmp);
        free(pwd);
        free(prompt);
    }
}
