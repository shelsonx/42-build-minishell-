/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:46:48 by progerio          #+#    #+#             */
/*   Updated: 2022/11/04 22:28:54 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_pointer(t_ulong pointer_size)
{
	size_t	num_size;
	char	*arr;

	if (!pointer_size)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putchar_fd('0', 1);
	ft_putchar_fd('x', 1);
	arr = ft_itoa_base(pointer_size, HEX_BASE_LOWER);
	ft_putstr_fd(arr, 1);
	num_size = (ft_strlen(arr));
	free(arr);
	return (num_size + 2);
}
