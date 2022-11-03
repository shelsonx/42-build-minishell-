#include "../libs/libft/libft.h"
#include <unistd.h>
#include <stdio.h>

static void show_current_dir(void)
{
    char cwd[256];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd error()");
    else
        ft_printf("current dir:\n %s\n", cwd);
}

void    go_to_dir(char *path)
{
    int ch = chdir(path);

    if (ch == 0)
        ft_printf("Sucessful!\n");
    else
        ft_printf("Not sucessful!\n");
}

int main(void)
{
    show_current_dir();
    go_to_dir("../../");
    show_current_dir();
    return (0);
}
