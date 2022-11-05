#include "../../includes/minishell.h"

//-lreadline
//--suppressions=readline.supp

void    prompt()
{
    char    *line;

    while (TRUE)
    {
        line = readline("Minishell:");
        add_history(line);
		execute(line);
        free(line);
    }
}
