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
# include <fcntl.h>

# define TRUE 1
# define FALSE 0
# define MININT -2147483648 
# define MAXINT 2147483647
# define CAPACITY 50000 // Size of the Hash Table
# define METACHARS	"|<>&() "

typedef struct s_token
{
    int		type;
    char	*value;
}	t_token;

typedef struct s_tokenizer 
{
    char        current_char;
    int         pos;
	char		*content;
    char        *characteres;
	t_token		token;
}   t_tokenizer;

typedef struct s_htitem t_htitem;

struct s_htitem {
    char* key;
    char* value;
};

typedef struct s_linkedlist t_linkedlist;

struct s_linkedlist {
    t_htitem* item; 
    t_linkedlist* next;
};

typedef struct s_hashtable t_hashtable;

struct s_hashtable {
    t_htitem** items;
    t_linkedlist** overflow_buckets;
    int size;
    int count;
};

typedef struct s_builtin_vars 
{
    int         size;
    t_hashtable   *env;
}   t_builtin_vars;

typedef struct s_parser
{
	t_tokenizer	*tokenizer;
	t_token		*current_token;
	int			token_type;
	int			index_redirect;
	int			index;
	t_hashtable	*table;
	t_hashtable	*table_redirection;
	t_builtin_vars *builtin_vars;
}	t_parser;

typedef struct s_data {
	char    **pipeline;
	int		**fds;
	char	**args;
	int		fd_in;
	int		fd_out;
	t_builtin_vars *builtin_vars;
} t_data;

enum e_TOKENS 
{
	TK_WORD,
	TK_PARENTHESIS,
	TK_GREAT,
	TK_LESS,
	TK_DGREAT,
	TK_DLESS,
	TK_PIPE,
	TK_EOF,
	TK_ERROR
};

//builtin
char	*get_env_path(char *path, t_builtin_vars *builtin);
void	init_env(t_builtin_vars *builtin_vars, char **envp);
void	ft_env(t_builtin_vars *builtin_vars);
void	ft_pwd(t_builtin_vars *builtin_vars);
char    **get_env(t_builtin_vars *builtin_vars);

int	count_args(char **declar);
int	ft_echo(char **declar);

int	check_len(char **declar);
char check_str_nb(char *declar);
void	error_msg(char *declar, int status);
void	ft_exit(char **declar);

//execute
char	**get_pipeline(t_data *data, t_parser *parser_data, int position);
int     execute(t_parser *parser_data);
//after remove
char **create_args(char **pipeline);

//prompt
void    prompt(char **envp);

//utils pipes
void	ft_free_fds(int **fds);
void	ft_close_fds(int **fds);

//paths
char	**get_paths_cmds(char *env_path);
char	*join_path_command(char *path, char *command);

//children processes
pid_t	create_child_process(void);
pid_t	execute_child_process(t_data *data);

//command
char	*get_exec_command(char *arg);
void	exec_one_command(t_data *data, int fd_in, int fd_out);
void	exec_first_command(t_data *data, int fd_in, int fd_out);
void	exec_middles_commands(t_data *data, t_parser *parser_data, int total_cmds_middles);
void	exec_last_command(t_data *data, int fd_in, int fd_out);
int		exists_commands(t_data *data);
int	new_get_fd_in(t_parser *parser_data, char *index_cmd);
int	new_get_fd_out(t_parser *parser_data, char *index_cmd);
void here_doc(int **fd, char *limiter);


//ht_functions
unsigned long hash_function(char* str);
t_htitem* create_item(char* key, char* value); 
void free_item(t_htitem* item);
void handle_collision(t_hashtable* table, unsigned long index, t_htitem* item);
void ht_delete(t_hashtable* table, char* key);

//ht_utils
t_hashtable* create_table(int size);
void free_hashtable(t_hashtable* table);
void ht_insert(t_hashtable* table, char* key, char* value);
char* ht_search(t_hashtable* table, char* key);

//linkedlist_utils
t_linkedlist* allocate_list ();
t_linkedlist* linkedlist_insert(t_linkedlist* list, t_htitem* item);
void free_linkedlist(t_linkedlist* list);
t_linkedlist** create_overflow_buckets(t_hashtable* table);
void free_overflow_buckets(t_hashtable* table);

//pipes
int     **create_pipes(int amount);

//signals
void	sighandler(int sigtype);

//exit program
void    exit_program(t_data *data);

//get token
t_token get_word(t_tokenizer *tokenizer);
t_token get_parenthesis(t_tokenizer *tokenizer);
t_token get_great(t_tokenizer *tokenizer);
t_token get_less(t_tokenizer *tokenizer);
t_token get_pipe(t_tokenizer *tokenizer);

//lexical analyzer
char    *get_name_token(int type_token);
int is_eof(size_t *pos, char *content);
void init_tokenizer(t_tokenizer *tokenizer); 
t_token get_next_token(t_tokenizer *tokenizer);
t_token next_token(t_tokenizer *tokenizer);

//lexical resources
void 	add_char(t_tokenizer *tokenizer);
void 	invalid_token(t_tokenizer *tokenizer);
void    advance(t_tokenizer *tokenizer);
void    skip_space(t_tokenizer *tokenizer);
void    tk_word(t_tokenizer *tokenizer);
int 	is_quote(char c);


//parser
void    parser(t_parser *parser);

//expander
void expand_variable(char **args, t_builtin_vars *builtin_vars);
 int expand_simple_quotes(char **args, t_builtin_vars *builtin_vars);
int expand_double_quotes(char **args, t_builtin_vars *builtin_vars);
int contains_quotes(char **args, int quote);
int get_amount_character(char **args, char character);
#endif /* MINISHELL */