/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newlinecpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:40:36 by progerio          #+#    #+#             */
/*   Updated: 2022/08/17 02:45:30 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_newlinecpy(char *dst, const char *src, size_t index)
{
	size_t	i;

	i = 0;
	while (src[i] != '\n' && src[i])
		dst[index++] = src[i++];
	if (src[i] == '\n')
		dst[index++] = '\n';
	dst[index] = '\0';
	return (index);
}
