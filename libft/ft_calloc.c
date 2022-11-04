/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 23:36:56 by progerio          #+#    #+#             */
/*   Updated: 2022/08/17 02:27:40 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	*ptr;
	int		space;

	space = nmemb * size;
	if (nmemb != 0 && space / size != nmemb)
		return (NULL);
	ptr = malloc(space);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, space);
	return (ptr);
}
