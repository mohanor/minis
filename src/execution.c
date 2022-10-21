/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:22:44 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 23:01:44 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_env2(void)
{
	int		i;
	char	**ptr;
	t_env	*tmp;

	i = 0;
	tmp = g_var.env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = g_var.env;
	ptr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	add_garbage(ptr);
	while (tmp)
	{
		ptr[i++] = ft_strjoin(ft_strjoin(tmp->data, "="), tmp->value);
		tmp = tmp->next;
	}
	ptr[i] = NULL;
	return (ptr);
}

void	get_status(void)
{
	int	status;

	while (1)
		if (waitpid(-1, &status, 0) == -1)
			break ;
	if (WIFEXITED(status))
		g_var.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (status == 3)
			printf("^\\Quit: 3\n");
		g_var.status = 128 + WTERMSIG(status);
	}
}

void	dup_1(int fd[2])
{
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
}

void	dup_0(int fd[2])
{
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}

void	fork_resource(void)
{
	ft_puterror("fork", ": Resource temporarily unavailable\n");
	g_var.status = 1;
}

void	sub_main(t_pipe *tmp, int fd[2])
{
	if (tmp->next)
		dup_1(fd);
	ft_execution(tmp->cmd);
}

void	main_exc(t_pipe *lst)
{
	t_pipe	*tmp;
	int		fd[2];
	int		pid;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next)
			pipe(fd);
		pid = fork();
		if (pid < 0)
		{
			fork_resource();
			return ;
		}
		if (pid == 0)
			sub_main(tmp, fd);
		if (tmp->next)
			dup_0(fd);
		else
			close(0);
		tmp = tmp->next;
	}
}

void	ft_start_exe(t_pipe *lst)
{
	if (lst->next == NULL)
		if (ft_bulletin(lst->cmd))
			return ;
	main_exc(lst);
	get_status();
}

void	ft_get_args_1(int *i, char *cmd, char c, t_redic **lst_of_red)
{
	int	j;

	(*i)++;
	if (cmd[*i] == c)
	{
		(*i)++;
		c = 'a';
	}
	while (cmd[*i] && cmd[*i] == ' ')
		(*i)++;
	j = *i;
	while (cmd[*i] && !ft_strchr(" ><", cmd[*i]))
		(*i)++;
	if (cmd[*i])
		(*i)--;
	ft_lstadd_back_red(lst_of_red, ft_substr(cmd, j, *i - j + 1), c);
}

void	ft_get_args_and_red(char *cmd, t_pipe **lst_of_args, t_redic **lst_of_red)
{
	t_pipe	*tmp;
	int		i;
	int		j;
	char	c;

	i = 0;
	tmp = *lst_of_args;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			// ft_get_args_1(&i, cmd, cmd[i], lst_of_red);
			c = cmd[i];
			i++;
			if (cmd[i] == c)
			{
				i++;
				c = 'a';
			}
			while (cmd[i] && cmd[i] == ' ')
				i++;
			j = i;
			while (cmd[i] && !ft_strchr(" ><", cmd[i]))
				i++;
			if (cmd[i])
				i--;
			ft_lstadd_back_red(lst_of_red, ft_substr(cmd, j, i - j + 1), c);
		}
		else if (cmd[i] != ' ')
		{
			j = i;
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '>' && cmd[i] != '<')
			{
				if (cmd[i] && (cmd[i] == '\"' || cmd[i] == '\''))
				{
					c = cmd[i];
					i++;
					while (cmd[i] && (cmd[i] != c))
						i++;
				}
				i++;
			}
			ft_lstadd_back(lst_of_args, ft_substr(cmd, j, i - j));
		}
		i++;
	}
}

int	size_of_lst(t_pipe *lst_of_args)
{
	t_pipe	*tmp;
	int		i;

	i = 0;
	tmp = lst_of_args;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**args_lst_to_tab(t_pipe *lst_of_args)
{
	int		len;
	char	**args;
	t_pipe	*tmp;
	int		i;

	len = size_of_lst(lst_of_args);
	args = (char **)malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	add_garbage(args);
	i = 0;
	tmp = lst_of_args;
	while (tmp)
	{
		args[i++] = tmp->cmd;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

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
		if (errno == 13)
		{
			ft_puterror(ptr[0], ":Permission denied\n");
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
