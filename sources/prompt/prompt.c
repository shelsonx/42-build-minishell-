#include "../../includes/minishell.h"

//-lreadline
//--suppressions=readline.supp

void    prompt()
{
    char    *line;

    while (TRUE)
    {	
		signal(SIGQUIT, sighandler);
		signal(SIGINT, sighandler);
        line = readline("Minishell:");
        add_history(line);
		execute(line);
        free(line);
    }
}
