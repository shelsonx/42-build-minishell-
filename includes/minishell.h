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

enum e_TOKENS 
{
	TK_WORD,
	TK_DIGIT,
	TK_QUOTE,
	TK_PARENTHESIS,
	TK_OPERATOR,
	TK_GREAT,
	TK_LESS,
	TK_DGREAT,
	TK_DLESS,
	TK_PIPE
};

//execute
int     execute(char *line);
//after remove
char 	**create_args(char **pipeline, int pos_cmd, int pos_param);

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
void	exec_one_command(t_data *data, int fd_in, int fd_out);
void	exec_first_command(t_data *data, int fd_in);
void	exec_middles_commands(t_data *data, int total_cmds_middles);
void	exec_last_command(t_data *data, int index, int fd_out, int pos_cmd, int pos_param);

//children processes
pid_t	create_child_process(void);
pid_t	execute_child_process(t_data *data);

//exit program
void    exit_program(t_data *data);

#endif /* MINISHELL */