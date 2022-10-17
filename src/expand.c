/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:45:00 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/16 22:49:51 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_name(char *str)
{
	char	*ret;
	int		i;
	
	i = 0;
	ret = ft_strdup("");
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		ret = ft_strjoin(ret, ft_substr(str, i, 1));
		i++;
	}
	return ret;
}

char	*ft_expand(char *cmd)
{
	int		i;
	char	*ret;
	char	*name;
	char	*value;
	int		expand;

	expand = 1;
	i = 0;
	ret = ft_strdup("");
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			expand = !expand;
		if (expand == 1 && cmd[i] == '$')
		{
			if (cmd[i + 1] == '?')
			{
				ret = ft_strjoin(ret, ft_itoa(g_var.status));
				i += 2;
				continue;
			}
			if (ft_isalpha(cmd[i + 1]) || cmd[i + 1] == '_')
			{
				name = get_name(&cmd[i + 1]);
				value = get_from_env(name);
				// value = NULL;
				if (value)
					ret = ft_strjoin(ret, value);
				else
					ret = ft_strjoin(ret, "");
				// ret = ft_strjoin(ret, (char *)((long)value * (value != NULL) + (long)"" * (value == NULL)));
				i += ft_strlen(name) + 1;
				continue ;
			}
		}
		ret = ft_strjoin(ret, ft_substr(cmd, i, 1));
		if (cmd[i] == '$' && cmd[i + 1] == '$')
			ret = ft_strjoin(ret, ft_substr(cmd, i++, 1));
		i++;
	}
	return (ret);
}