/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_strs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shelson <shelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:45:24 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/01/03 22:33:03 by shelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concat_strs(char *str1, char *str2, char *separator)
{
	char	*joinned;
	char	*tmp;

	tmp = ft_strjoin(str1, separator);
	joinned = ft_strjoin(tmp, str2);
	free(tmp);
	free(str1);
	free(str2);
	return (joinned);
}