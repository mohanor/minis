/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:57:16 by matef             #+#    #+#             */
/*   Updated: 2022/10/20 01:23:04 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_garbage(void *ptr)
{
	t_garbage	*new;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	if (!new)
		return ;
	new->ptr = ptr;
	new->next = NULL;
	if (!g_var.garbage)
		g_var.garbage = new;
	else
	{
		new->next = g_var.garbage;
		g_var.garbage = new;
	}
	// t_garbage   *tmp;

    // tmp = g_var.garbage;
    // int i = 0;
    // while (tmp)
    // {
    //     i++;
    //     tmp = tmp->next;
    // }
    // printf("%d\n", i);
}


void	free_garbage(void)
{
	t_garbage	*tem;

	while (g_var.garbage)
	{
		tem = g_var.garbage;
		g_var.garbage = (g_var.garbage)->next;
		if (tem->ptr)
			free(tem->ptr);
		free(tem);
	}
}

/*
void	free_garbage(void)
{
	t_garbage	*tem;

	while (g_var.garbage)
	{
		tem = g_var.garbage;
		g_var.garbage = (g_var.garbage)->next;
		if (tem->ptr)
			free(tem->ptr);
		free(tem);
	}
}
*/
