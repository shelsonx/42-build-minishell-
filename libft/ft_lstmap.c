/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:47:04 by progerio          #+#    #+#             */
/*   Updated: 2022/08/17 02:41:28 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_clear(t_list **lst, void (*del)(void*))
{
	ft_lstclear(lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*aux;

	if (!lst)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (new_lst == NULL)
		ft_clear(&new_lst, del);
	while (lst->next)
	{
		aux = ft_lstnew(f(lst->next->content));
		if (aux == NULL)
			ft_clear(&new_lst, del);
		ft_lstadd_back(&new_lst, aux);
		lst = lst->next;
	}
	return (new_lst);
}
