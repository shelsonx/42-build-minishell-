/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:43:04 by progerio          #+#    #+#             */
/*   Updated: 2022/11/04 22:13:03 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle_this(int type, va_list ap, size_t *chars_written)
{
	if (type == INT)
		*chars_written += ft_put_decimal(va_arg(ap, int));
	else if (type == CHAR)
		*chars_written += ft_put_character(va_arg(ap, int));
	else if (type == STR)
		*chars_written += ft_put_string(va_arg(ap, char *));
	else if (type == PTR)
		*chars_written += ft_put_pointer((t_ulong) va_arg(ap, void *));
	else if (type == UINT)
		*chars_written += ft_put_unsigned(va_arg(ap, t_uint));
	else if (type == HEX_L)
		*chars_written += ft_put_hex_lower(va_arg(ap, t_uint));
	else if (type == HEX_U)
		*chars_written += ft_put_hex_upper(va_arg(ap, t_uint));
	else if (type == PERCENT)
		*chars_written += ft_put_percent();
	else
		return (FALSE);
	return (TRUE);
}

static int	ft_get_arg_type(char type)
{
	if (!type)
		return (FALSE);
	if (type == 'd' || type == 'i')
		return (INT);
	else if (type == 'c')
		return (CHAR);
	else if (type == 's')
		return (STR);
	else if (type == 'p')
		return (PTR);
	else if (type == 'u')
		return (UINT);
	else if (type == 'x')
		return (HEX_L);
	else if (type == 'X')
		return (HEX_U);
	else if (type == '%')
		return (PERCENT);
	return (FALSE);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	chars_written;
	int		type;

	chars_written = 0;
	va_start(ap, format);
	while (*format && *format - 1 != '\0')
	{
		type = 0;
		while (*format != '%' && *format)
		{
			ft_putchar_fd(*format++, 1);
			chars_written++;
		}
		if (*format == '%')
			type = ft_get_arg_type(*++format);
		if (!ft_handle_this(type, ap, &chars_written))
			break ;
		format++;
	}
	va_end(ap);
	return (chars_written);
}
