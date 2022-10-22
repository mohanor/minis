/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:02:48 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 01:47:24 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_convert_to_lower(char *cmd)
{
    int i;

    i = 0;
    while (*cmd)
    {
        if (*cmd >= 'A' && *cmd <= 'Z')
            *cmd += 32;
        cmd++;
    }
}

void	ft_new_env(char **env)
{
	t_env	**new_env;
	char	**splt;
	int		i;

	g_var.env = NULL;
	new_env = &g_var.env;
	i = 0;
	while (env[i])
	{
		splt = ft_split(env[i], '=');
		ft_lst_addback_env(new_env, ft_lstnew_env(splt[0], splt[1]));
		i++;
	}
}

void	only_export(void)
{
	t_env	*env;

	env = g_var.env;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->data, env->value);
		else
			printf("declare -x %s\n", env->data);
		env = env->next;
	}
}

int	only_space(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] != ' ')
			return (0);
	}
	return (1);
}

void	handler(int sig)
{
	(void)sig;
	g_var.doc = 1;
	rl_done = 1;
}
