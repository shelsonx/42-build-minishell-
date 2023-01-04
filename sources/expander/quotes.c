#include "../../includes/minishell.h"

void    remove_quotes(char **args)
{
    int     x;
    char    *quote;

    x = 0;
    quote = ft_calloc(sizeof(char *), 2);
    while (args[x])
    {
        if (is_quote(args[x][0]) && is_quote(args[x][ft_strlen(args[x]) -1]))
        {
            quote[0] = args[x][0];
            args[x] = ft_replace_str(args[x], quote, "");
        }
        while (args[x][ft_strlen(args[x]) -1] == quote[0])
        {
            args[x] = ft_replace_str(args[x], quote, "");
        }
        x++;
    }
}
