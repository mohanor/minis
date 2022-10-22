/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:55:51 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 17:54:36 by skasmi           ###   ########.fr       */
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

void	ft_aux_export(char *var, char *val)
{
	t_env	*new;
	t_env	*tmp;

	tmp = g_var.env;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	add_garbage(new);
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
}

void	ft_export_middel(char *var, char *val)
{
	if (var[ft_strlen(var) - 1] == '+')
	{
		var = ft_substr(var, 0, ft_strlen(var) - 1);
		if (get_from_env(var))
			val = ft_strjoin(get_from_env(var), val);
	}
	ft_unset(var);
}

void	ft_export(char **cmd)
{
	char	*val;
	char	*var;
	int		len;
	char	*to_exp;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		to_exp = cmd[i];
		if (ft_strstr(to_exp, "="))
		{
			val = ft_strstr(to_exp, "=") + 1;
			len = ft_strlen(to_exp) - ft_strlen(val) - 1;
			var = ft_substr(to_exp, 0, len);
			ft_export_middel(var, val);
		}
		else
		{
			ft_unset(cmd[i]);
			var = cmd[i];
			val = NULL;
		}
		ft_aux_export(var, val);
	}
}
