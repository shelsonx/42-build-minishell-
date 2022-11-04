/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:46:18 by progerio          #+#    #+#             */
/*   Updated: 2022/11/04 22:28:38 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_decimal(int decimal)
{
	size_t	num_size;

	num_size = 1;
	ft_putnbr_fd(((long) decimal), 1);
	while (decimal >= 10 || decimal <= -10)
	{
		decimal /= 10;
		num_size++;
	}
	if (decimal < 0)
		return (num_size + 1);
	return (num_size);
}
