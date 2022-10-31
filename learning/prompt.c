#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//-lreadline
//--suppressions=readline.supp
int main(void)
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
