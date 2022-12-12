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

#define CAPACITY 50000 // Size of the Hash Table

typedef struct s_data {
	char    **pipeline;
	int		**fds;
	char	**args;
	int		fd_in;
	int		fd_out;
} t_data;

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

typedef struct s_htItem s_htItem;

struct s_htItem {
    char* key;
    char* value;
};

typedef struct s_linkedList s_linkedList;

struct s_linkedList {
    s_htItem* item; 
    s_linkedList* next;
};

typedef struct s_hashTable s_hashTable;

struct s_hashTable {
    s_htItem** items;
    s_linkedList** overflow_buckets;
    int size;
    int count;
};

typedef struct s_parser
{
	t_tokenizer	*tokenizer;
	t_token		*current_token;
	int			token_type;
	int			index_redirect;
	int			index;
	s_hashTable	*table;
	s_hashTable	*table_redirection;
}	t_parser;

enum e_TOKENS 
{
	TK_WORD,
	TK_PARENTHESIS,
	TK_GREAT,
	TK_LESS,
	TK_DGREAT,
	TK_DLESS,
	TK_PIPE,
	TK_EOF
};

//execute
int     execute(t_parser *parser_data);
//after remove
char **create_args(char **pipeline);

//prompt
void    prompt();

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
s_htItem* create_item(char* key, char* value); 
void free_item(s_htItem* item);
void handle_collision(s_hashTable* table, unsigned long index, s_htItem* item);
void ht_delete(s_hashTable* table, char* key);

//ht_utils
s_hashTable* create_table(int size);
void free_hashtable(s_hashTable* table);
void ht_insert(s_hashTable* table, char* key, char* value);
char* ht_search(s_hashTable* table, char* key);

//linkedlist_utils
s_linkedList* allocate_list ();
s_linkedList* linkedlist_insert(s_linkedList* list, s_htItem* item);
void free_linkedlist(s_linkedList* list);
s_linkedList** create_overflow_buckets(s_hashTable* table);
void free_overflow_buckets(s_hashTable* table);

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
void    identifier(t_tokenizer *tokenizer);

//parser
void    parser(t_parser *parser);

#endif /* MINISHELL */