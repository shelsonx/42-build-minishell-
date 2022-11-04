/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 02:56:53 by progerio          #+#    #+#             */
/*   Updated: 2022/08/23 19:47:54 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_handle_buffer(char *buffer)
{
	size_t		i;
	char		*str;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	ft_strlcpy(buffer, &buffer[i + 1], BUFFER_SIZE - i);
	if (!*buffer)
		return (NULL);
	str = malloc(sizeof(char) * (BUFFER_SIZE - i + 1));
	if (!str)
		return (NULL);
	ft_newlinecpy(str, buffer, 0);
	return (str);
}

static char	*ft_realloc(char *str, size_t length)
{
	char	*tmp;

	if (!str)
		str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	else
	{
		tmp = malloc(sizeof(char) * (length + BUFFER_SIZE + 1));
		ft_strlcpy(tmp, str, length + 1);
		free(str);
		str = tmp;
	}
	if (!str)
		return (NULL);
	return (str);
}

static char	*ft_read(int fd, char *buffer, char *str)
{
	size_t	i;
	int		read_ret;

	i = ft_strlen(str);
	read_ret = BUFFER_SIZE;
	while (read_ret == BUFFER_SIZE)
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (read_ret < 1)
			break ;
		buffer[read_ret] = '\0';
		str = ft_realloc(str, i);
		i = ft_newlinecpy(str, buffer, i);
		if (read_ret < BUFFER_SIZE || str[i - 1] == '\n')
			break ;
	}
	if (read_ret < 1 && !str)
	{
		free(buffer);
		return (NULL);
	}
	return (str);
}

char	*ft_get_next_line(int fd)
{
	static char	*buffer[MAX_FD_VALUE];
	char		*str;

	if (fd < 0 || fd >= MAX_FD_VALUE || BUFFER_SIZE < 1)
		return (NULL);
	str = NULL;
	if (!buffer[fd])
		buffer[fd] = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	else if (ft_strchr(buffer[fd], '\n'))
	{
		str = ft_handle_buffer(buffer[fd]);
		if (ft_strchr(str, '\n'))
			return (str);
	}
	str = ft_read(fd, buffer[fd], str);
	if (!str)
		buffer[fd] = NULL;
	return (str);
}
