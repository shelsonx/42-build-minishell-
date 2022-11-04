/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:33:16 by progerio          #+#    #+#             */
/*   Updated: 2022/08/17 02:54:37 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*str;

	begin = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, s1[begin]))
		begin++;
	end = ft_strlen(s1);
	while (end && ft_strchr(set, s1[end]))
		end--;
	str = ft_substr(s1, begin, end - begin + 1);
	return (str);
}
