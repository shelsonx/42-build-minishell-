/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:33:15 by progerio          #+#    #+#             */
/*   Updated: 2022/08/17 02:53:47 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	res;

	len = ft_strlen(s2);
	if (s2[0] == '\0')
		return ((char *)s1);
	while (*s1 && (n-- >= len))
	{
		res = ft_strncmp(s1, s2, len);
		if (res == 0 && *s1 == *s2)
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
