/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:28 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/18 23:10:46 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char 	*getname(char *str)
{
	int i;
	int j;
	
	j = 0;
	i = 0;
	while(!ft_isalpha(str[i]))
		i++;
	char *ret = malloc(ft_strlen(str) - i);
	while(i < ft_strlen(str))
	{
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[i] = '\0';
	return(ret);
}

char *getlast(char *str)
{
	int j;
	int i;
	
	i = 0;
	j = ft_strlen(str);
	while(str[j] != '/')
		j--;
	char *ret = malloc(j);
	while(i < j)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return(ret);	
}

void	ft_cd(char **path)
{
	char	*home;
	t_env	*t;

	t = g_var.env;
	if(ft_strcmp(path[1], ".") == 0)
	{
	// 	if (errno)
	// 		printf("error retrieving current directory: getcwd:\
	// cannot access parent directories: No such file or directory\n");
		return;
	}
	else if(ft_strcmp(path[1],"..") == 0)
	{
		chdir("..");
		while (t)
		{
			if (ft_strcmp("PWD", t->data) == 0)
				t->value = getlast(t->value);
			t = t->next;
		}
		return;
	}
	else if (path[1] == NULL)
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_puterror("cd", ": HOME not set");
			return ;
		}
		chdir(home);
		while (t)
		{
			if (ft_strcmp("PWD", t->data) == 0)
			{
				t->value = home;
				return;
			}
			t = t->next;
		}
		// return;
	}
	else if (path[1])
	{
		if(access(path[1], X_OK) == -1)
		{
			ft_puterror(path[1], ": No such file or directory\n");
			return;
		}
		chdir(path[1]);
		while (t)
		{
			if (ft_strcmp("PWD", t->data) == 0)
			{
				t->value = ft_strjoin(t->value,"/");
				t->value = ft_strjoin(t->value,getname(path[1]));
				return;
			}
			t = t->next;
		}
	}	
	ft_puterror(path[1], ": No such file or directory\n");

	
	return ;
}
