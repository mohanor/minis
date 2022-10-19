/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:55:51 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/19 00:59:12 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_from_env(char *var)
{
	t_env	*tmp;

	tmp = g_var.env;
	while (tmp)
	{
		if (!ft_strcmp(var, tmp->data))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_export(char **cmd)
{
	t_env	*tmp;
	char	*val;
	char	*var;
	int		len;
	int		i;
	char	*to_exp;
	t_env	*new;

	tmp = g_var.env;
	i = 1;

	while (cmd[i])
	{
		printf("%s\n", cmd[i]);
		to_exp = cmd[i];
		if (ft_strstr(to_exp, "="))
		{
			val = ft_strstr(to_exp, "=") + 1;
			len = ft_strlen(to_exp) - ft_strlen(val) - 1;
			var = ft_substr(to_exp, 0, len);
			if (var[ft_strlen(var) - 1] == '+')
			{
				var = ft_substr(var, 0, ft_strlen(var) - 1);
				if (get_from_env(var))
					val = ft_strjoin(get_from_env(var), val);
			}
			ft_unset(var);
		}
		else
		{
			ft_unset(cmd[i]);
			var = cmd[i];
			val = NULL;
		}
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return ;
			new->data = var;
			new->value = val;
			new->next = NULL;
			if (!g_var.env)
				g_var.env = new;
			else
			{
				tmp = g_var.env;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new;
				new->prev = tmp;
			}
		i++;
	}
}