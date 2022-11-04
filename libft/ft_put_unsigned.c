/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:47:02 by progerio          #+#    #+#             */
/*   Updated: 2022/11/04 22:29:01 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_unsigned(t_uint uint)
{
	size_t	num_size;

	num_size = 1;
	ft_putnbr_fd(((long) uint), 1);
	while (uint >= 10)
	{
		uint /= 10;
		num_size++;
	}
	return (num_size);
}
