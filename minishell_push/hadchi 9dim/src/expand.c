/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:45:00 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 02:17:56 by skasmi           ###   ########.fr       */
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

// void	ft_aux_expand(char *cmd)
// {
// 	char	*ret;
// 	char	*name;
// 	char	*value;
// 	int 	i;
	
// 	i = 0;
// 	if (ft_isalpha(cmd[i + 1]) || cmd[i + 1] == '_')
// 	{
// 		name = get_name(&cmd[i + 1]);
// 		value = get_from_env(name);
// 		if (value)
// 			ret = ft_strjoin(ret, value);
// 		else
// 			ret = ft_strjoin(ret, "");
// 		i += ft_strlen(name) + 1;
// 	}
// }

char	*ft_expand(char *cmd)
{
	int		i;
	char	*ret;
	char	*name;
	char	*value;
	int		expand;

	i = 0;
	expand = 1;
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
				if (value)
					ret = ft_strjoin(ret, value);
				else
					ret = ft_strjoin(ret, "");
				i += ft_strlen(name) + 1;
				continue ;
			}
			// ft_aux_expand(cmd);
		}
		ret = ft_strjoin(ret, ft_substr(cmd, i, 1));
		if (cmd[i] == '$' && cmd[i + 1] == '$')
			ret = ft_strjoin(ret, ft_substr(cmd, i++, 1));
		i++;
	}
	return (ret);
}
