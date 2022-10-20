/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:28 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/19 23:22:58 by matef            ###   ########.fr       */
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

void	ft_change_pwd_and_old(char *ptr, char	*cwd)
{
	t_env	*t;
	// ;
	
	t = g_var.env;
	while (t)
		{
			if (ft_strcmp(ptr, t->data) == 0)
			{
				if (!cwd)
					perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
				else
				{
					t->value = cwd; // free
				}
				return ;
			}
			t = t->next;
		}
}

void	ft_cd(char **path)
{
	char	*home;
	int		nb;
	t_env	*t;
	char 	*s;

	t = g_var.env;
	nb = 0;
	if (path[1] == NULL)
	{
		home = get_from_env("HOME");
		if (!home)
		{
			ft_puterror("cd", ": HOME not set");
			write (1, "\n", 1);
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
	if (!path || !*path || ft_strncmp(path[0], "cd", 255))
		return ;
	if (path[1] && path[1][0] == '-' && path[1][1] != '\0' && path[1][1] != '-')
		ft_error_cmd(path);
	else if (path[1])
	{
		s = getcwd(NULL, 0);
		add_garbage(s);
		ft_change_pwd_and_old("OLDPWD", s);
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