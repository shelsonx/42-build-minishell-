/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:38:57 by progerio          #+#    #+#             */
/*   Updated: 2022/08/29 17:57:01 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(t_ulong n, char *base)
{
	char		*arr;
	size_t		base_size;
	size_t		num_size;
	t_ulong		num;

	num = n;
	num_size = 1;
	base_size = ft_strlen(base);
	while (n >= base_size)
	{
		n /= base_size;
		num_size++;
	}
	arr = ft_calloc((num_size + 1), sizeof(char));
	if (arr == NULL)
		return (NULL);
	while (num_size--)
	{
		arr[num_size] = base[num % base_size];
		num /= base_size;
	}
	return (arr);
}
