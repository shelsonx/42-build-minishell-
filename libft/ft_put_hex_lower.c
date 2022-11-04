/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex_lower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:46:28 by progerio          #+#    #+#             */
/*   Updated: 2022/11/04 22:28:43 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_hex_lower(t_uint num)
{
	size_t	num_size;
	char	*arr;

	arr = ft_itoa_base(num, HEX_BASE_LOWER);
	ft_putstr_fd(arr, 1);
	num_size = ft_strlen(arr);
	free(arr);
	return (num_size);
}
