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

void    builtin_cd(char *path)
{
    if (path == NULL)
        getenv("HOME");
    chdir(path);
}

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    char    *key;
    int length;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PWD", 3) == 0)
        {
            ft_printf("%s\n", envp[i]);
            envp[i] = ft_strjoin("PWD=", getenv("HOME"));
        }
        i++;
    }
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PWD", 3) == 0)
            ft_printf("%s\n", envp[i]);
        i++;
    }
    
    /* ft_printf("%s\n", getenv("PATH"));
    show_current_dir();
    builtin_cd(argv[1]);
    show_current_dir(); */
}
