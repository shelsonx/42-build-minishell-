/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:48:00 by progerio          #+#    #+#             */
/*   Updated: 2022/08/17 02:55:01 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	len_max;
	size_t	size;

	size = ft_strlen(s);
	len_max = size - start;
	if (s == NULL)
		return (NULL);
	if (start > size)
	{
		len = 1;
		start = 0;
	}
	else if (start + len > size)
		len = len_max + 1;
	else
		len = len + 1;
	s1 = malloc(len);
	if (s1 == NULL)
		return (NULL);
	ft_strlcpy(s1, s + start, len);
	return (s1);
}
