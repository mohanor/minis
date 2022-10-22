/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:54:58 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 01:55:36 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (0);
}


char	*lexter_to_string(t_lexm *lxm)
{
	char	*ret;

	ret = ft_strdup("");
	while (lxm)
	{
		ret = ft_strjoin(ret, ft_strjoin(lxm->cmd, " "));
		lxm = lxm->next;
	}
	return (ret);
}

void	handle_sig(int pid)
{
	(void)pid;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}