/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:56:16 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/19 21:13:22 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_more_then_one(char **ptr)
{
	int	i;

	i = 1;
	while (ptr[i])
	{
		ft_unset(ptr[i]);
		i++;
	}
}

void	ft_unset(char *cmd)
{
	t_env	*tmp_next;
	t_env	*tmp_prev;
	t_env	*tmp;

	tmp = g_var.env;
	while (tmp)
	{
		if (ft_strcmp(cmd, tmp->data) == 0)
		{
			if (tmp && tmp->next == NULL && tmp->prev == NULL)
			{
				printf("jjjj\n");
				g_var.env = NULL;
				break ;
			}
			else if (tmp && tmp->next && tmp->prev == NULL)
			{
				g_var.env = g_var.env->next;
				break ;
			}
			else if (tmp && tmp->next == NULL && tmp->prev)
			{
				tmp->prev->next = NULL;
				break ;
			}
			tmp_next = tmp->next;
			tmp_prev = tmp->prev;
			tmp_prev->next = tmp_next;
			tmp_next->prev = tmp_prev;
			break ;
		}
		tmp = tmp->next;
	}
}