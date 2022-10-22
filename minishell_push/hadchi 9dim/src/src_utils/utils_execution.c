/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:59:34 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 20:55:02 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_puterror(char *err, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(msg, 2);
}

void	ft_execution(char *cmd)
{
	t_pipe	*lst_of_args;
	t_redic	*lst_of_red;
	char	**single_path;
	char	**ptr;
	int		i;

	lst_of_args = NULL;
	lst_of_red = NULL;
	ft_get_args_and_red(cmd, &lst_of_args, &lst_of_red);
	if (!lst_of_args)
		exit (0);
	ptr = args_lst_to_tab(lst_of_args);
	i = -1;
	if (lst_of_red)
		run_rediction(lst_of_red);
	ft_convert_to_lower(ptr[0]);
	if (!access(ptr[0], F_OK))
	{
		execve(ptr[0], ptr, ft_get_env2());
		if (errno == 13)
		{
			ft_puterror(ptr[0], ":Permission denied\n");
			exit (126);
		}
	}
	else if ( ft_strchr(ptr[0], '/'))
	{
		execve(ptr[0], ptr, ft_get_env2());
		if (errno == 2)
		{
			ft_puterror(ptr[0], ": No such file or directory\n");
			exit (126);
		}
	}
	else
	{
		if (getenv("PATH"))
		{
			single_path = ft_split(getenv("PATH"), ':');
			while (single_path[++i])
				execve(ft_strjoin(ft_strjoin(single_path[i], "/"), ptr[0]), ptr, ft_get_env2());
		}
		ft_puterror(ptr[0], ":command not found\n");
		exit(127);
	}
}
