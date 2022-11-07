/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shelson <shelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:23:05 by progerio          #+#    #+#             */
/*   Updated: 2022/11/07 10:04:37 by shelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int **create_pipes(int amount)
{
	int	i;
    int **tube;

	tube = ft_calloc
		(sizeof(int **), (amount + 1));
	i = 0;
	while (i < amount)
	{
		tube[i] = ft_calloc(sizeof(int *), 2);
		if (pipe(tube[i]) < 0)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		i++;
	}
    return (tube);
}
