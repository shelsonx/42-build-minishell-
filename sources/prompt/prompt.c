#include "../../includes/minishell.h"

//-lreadline
//--suppressions=readline.supp
void    prompt()
{
    char    *line;

    while (1)
    {
        line = readline("Minishell:");
        add_history(line);
        printf("%s\n", line);
        free(line);
    }
}