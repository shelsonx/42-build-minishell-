/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:36:43 by progerio          #+#    #+#             */
/*   Updated: 2022/08/17 02:48:30 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_string(char const *s, char c)
{
	int	i;
	int	n_word;
	int	control;

	i = 0;
	control = 0;
	n_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && control == 0)
		{
			control = 1;
			n_word++;
		}
		else if (s[i] == c)
			control = 0;
		i++;
	}
	return (n_word);
}

static void	add_string(char const *s, char c, char **split)
{
	size_t	len;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	len = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (i != len)
			{
				split[j] = ft_substr(s, len, i - len);
				j++;
			}
			len = i + 1;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;

	i = count_string(s, c);
	split = malloc(sizeof(char *) * (i + 1));
	if (split == NULL)
		return (NULL);
	add_string(s, c, split);
	split[i] = NULL;
	return (split);
}
