/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shelson <shelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:32:44 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/01/03 22:39:04 by shelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# define BUFFER_SIZE 42

enum	e_boolean {false, true};

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
char	ft_isdgreat(char *c);
char	ft_isdless(char *c);
int		ft_isgreat(int c);
int		ft_isless(int c);
int		ft_isoperator(int c);
int		ft_isparenthesis(int c);
int		ft_ispipe(int c);
int		ft_isprint(int c);
int		t_isquote(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c);
char	*ft_strcpy(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *src);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char delimiter);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new_node);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_node);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// GNL
char	*create_new_line(char *line, int line_size);
int		get_line_size(char	*line);
char	*join_read(int fd, char *line);
char	*finally(char *first_str, char *second_str);
char	*ft_get_next_line(int fd);

//FT_PRINTF
int		ft_printf(const char *format, ...);
char	*ft_ptr_hex(unsigned long int n, int base);
char	*ft_itoa_base(unsigned int n, int base, char character);
char	*ft_utoa(unsigned int n);

//MORE
int		ft_len_rows_tab(char **tab);
void	ft_free_tab(char **tab);
int		ft_abs(int value);
char	*ft_concat_strs(char *str1, char *str2, char *separator);
char    *ft_replace_str(const char *s, const char *old, const char *new);
#endif