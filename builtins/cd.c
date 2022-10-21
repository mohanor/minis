/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:28 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 03:03:42 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_change_dir(char *cmd)
{
	char	str[1024];

	if (ft_strncmp(cmd, ".", 255) && !getcwd(str, 1024))
		ft_putstr_fd("cd: error retrieving current directory: \
	getcwd: cannot access parent directories", 2);
	return (chdir(cmd));
}

void	ft_error_cmd(char **cmd)
{
	printf("%s: invalid option %c\n", cmd[0], cmd[1][1]);
	printf("cd: usage [without options] [dir]\n");
	return ;
}

void	ft_change_pwd_and_old(char *ptr, char *cwd)
{
	t_env	*t;

	t = g_var.env;
	while (t)
	{
		if (ft_strcmp(ptr, t->data) == 0)
		{
			if (!cwd)
			{
				perror("cd: error retrieving current directory: getcwd:\
					cannot access parent directories");
				return ;
			}
			else
				t->value = cwd;
			return ;
		}
		t = t->next;
	}
}

void	ft_if_null_path(char *home)
{
	t_env	*t;

	t = g_var.env;
	home = get_from_env("HOME");
	if (!home)
	{
		ft_puterror("cd", ": HOME not set");
		write(1, "\n", 1);
		return ;
	}
	chdir(home);
	while (t)
	{
		if (ft_strcmp("PWD", t->data) == 0)
		{
			t->value = home;
			return ;
		}
		t = t->next;
	}
	return ;
}

void	ft_cd(char **path)
{
	int		nb;
	t_env	*t;
	char	*s;

	t = g_var.env;
	nb = 0;
	if (path[1] == NULL)
		ft_if_null_path(path[1]);
	if (!path || !*path || ft_strncmp(path[0], "cd", 255))
		return ;
	if (path[1] && path[1][0] == '-' && path[1][1] != '\0' && path[1][1] != '-')
		ft_error_cmd(path);
	else if (path[1])
	{
		ft_if_path();
		nb = chdir(path[1]);
	}
	if (nb < 0)
		perror("cd");
	else
	{
		s = getcwd(NULL, 0);
		add_garbage(s);
		ft_change_pwd_and_old("PWD", s);
	}
}
