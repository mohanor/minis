/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:57:16 by matef             #+#    #+#             */
/*   Updated: 2022/10/18 23:01:50 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	ft_lstadd_front_garbage(t_garbage **lst, t_garbage *new)
{
	new->next = *lst;
	*lst = new;
}

t_garbage	*ft_lstnew_garbage(void *content)
{
	t_garbage	*node;

	node = (t_garbage *)malloc(sizeof(t_garbage));
	if (!node)
		return (0);
	node->ptr = content;
	node->next = 0;
	return (node);
}

t_garbage	*ft_lstlast_garbage(t_garbage *lst)
{
	t_garbage	*ptr;

	ptr = lst;
	while (ptr)
	{
		if (!ptr->next)
			return (ptr);
		ptr = ptr->next;
	}
	return (ptr);
}

void	add_garbage(void *value)
{
	t_garbage	*lstptr;

	if (!g_var.garbage)
	{
		ft_lstadd_front_garbage(&g_var.garbage, ft_lstnew_garbage(value));
		return ;
	}
	lstptr = ft_lstlast_garbage(g_var.garbage);
	lstptr->next = ft_lstnew_garbage(value);
}