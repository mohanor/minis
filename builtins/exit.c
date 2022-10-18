/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:55:31 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/18 23:06:03 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **cmd)
{
	if (!cmd[1])
	{
		printf("exit\n");
		exit(0);
	}
	else if (cmd[1] && is_num(cmd[1]) && !cmd[2])
	{
		printf("exit\n");
		exit(ft_atoi(cmd[1]));
	}
	else if (cmd[2] && is_num(cmd[1]))
	{
		printf("exit\n");
		printf("FRATELLO😈: %s: too many arguments\n", cmd[0]);
	}
	else if (is_num(cmd[1]) == 0 || cmd[2] || (is_num(cmd[2]) == 0 && cmd[2]))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required", cmd[1]);
		exit(255);
	}
	return (1);
}
