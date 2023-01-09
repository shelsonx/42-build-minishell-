#include "../../includes/minishell.h"


int main(void)
{
    int fd[2];
    char *args_1[] = {"/bin/tr", "o", "O", NULL};

    if (pipe(fd) < 0)
        return -1;
    
    int save = dup(STDOUT_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    ft_echo(ft_split("ola ola", ' '));
    close(fd[1]);
    
    dup2(save, STDOUT_FILENO);
    pid_t pid = fork();
    if (pid == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        execve(args_1[0], args_1, NULL);
    }
    /* close(fd[0]);
    close(fd[1]); */
   // waitpid(-1, NULL, 0);
  
    return (0);
}