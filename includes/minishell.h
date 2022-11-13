#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_data {
	char    **pipeline;
	int		**fds;
	char	**args;
	int		fd_in;
	int		fd_out;
} t_data;

enum    e_boolean {FALSE, TRUE};

//execute
int     execute(char *line);

//prompt
void    prompt();

//pipes
int     **create_pipes(int amount);

//utils pipes
void	ft_free_fds(int **fds);
void	ft_close_fds(int **fds);

//signals
void	sighandler(int sigtype);

//paths
char	**get_paths_cmds(char *env_path);
char	*join_path_command(char *path, char *command);

//command
char	*get_exec_command(char *arg);

#endif /* MINISHELL */