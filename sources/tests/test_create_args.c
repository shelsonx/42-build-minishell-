#include "../../includes/minishell.h"

char **create_args_2(char **pipeline)
{
    char *old;

    old = pipeline[0];
    
    pipeline[0] = ft_strdup("/bin/ls");
    free(old);
	return pipeline;
}

int main(void)
{
    char **pipeline = ft_split("ls -a -l -x -z -r", ' ');

    char **args = create_args_2(pipeline);

    int i = 0;
    while (i <= ft_len_rows_tab(pipeline))
    {
        ft_printf("%s\n", args[i]);
        i++;
    }
    ft_free_tab(args);
    return 0;
}