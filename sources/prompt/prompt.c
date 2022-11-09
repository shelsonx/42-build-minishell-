#include "../../includes/minishell.h"

//-lreadline
//--suppressions=readline.supp

void    prompt()
{
    char    *line;

    while (TRUE)
    {	
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
        line = readline("Minishell:");
        add_history(line);
		execute(line);
        free(line);
    }
}
