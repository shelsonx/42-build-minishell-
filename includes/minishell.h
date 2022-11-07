/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shelson <shelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:56:01 by progerio          #+#    #+#             */
/*   Updated: 2022/11/07 09:22:28 by shelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>

enum    e_boolean {FALSE, TRUE};

//execute
int     execute(char *line);

//prompt
void    prompt();

//pipes
int     **create_pipes(int amount);

//utils pipes
void	ft_free_fds(int **fds);
void	close_fds(int **fds);

#endif /* MINISHELL */