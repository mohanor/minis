/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:56:16 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 21:31:51 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_more_then_one(char **ptr)
{
	int	i;

	i = 1;
	while (ptr[i])
	{
		printf("%s\n", ptr[i]);
		ft_unset(ptr[i]);
		i++;
	}
}

void	ft_aux_unset(t_env *tmp_next, t_env *tmp_prev, t_env *tmp)
{
	if (tmp && tmp->next && tmp->prev)
	{
		tmp_next = tmp->next;
		tmp_prev = tmp->prev;
		tmp_prev->next = tmp_next;
		tmp_next->prev = tmp_prev;
	}
}

void	ft_unset(char *cmd)
{
	t_env	*tmp_next;
	t_env	*tmp_prev;
	t_env	*tmp;

	tmp_next = NULL;
	tmp_prev = NULL;
	tmp = g_var.env;
	while (tmp)
	{
		if (ft_strcmp(cmd, tmp->data) == 0)
		{
			if (tmp && tmp->next == NULL && tmp->prev == NULL)
				g_var.env = NULL;
			else if (tmp && tmp->next && tmp->prev == NULL)
				g_var.env = g_var.env->next;
			else if (tmp && tmp->next == NULL && tmp->prev)
				tmp->prev->next = NULL;
			else
				ft_aux_unset(tmp, tmp_next, tmp_prev);
			break ;
		}
		tmp = tmp->next;
	}
}
