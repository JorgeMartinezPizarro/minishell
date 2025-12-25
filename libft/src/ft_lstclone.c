/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:45:38 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/25 19:47:20 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstclone(t_list *lst, void *(*dup)(void *))
{
	t_list	*copy;
	t_list	*node;

	copy = NULL;
	while (lst)
	{
		node = ft_lstnew(dup(lst->content));
		if (!node)
		{
			ft_lstclear(&copy, free);
			return (NULL);
		}
		ft_lstadd_back(&copy, node);
		lst = lst->next;
	}
	return (copy);
}
