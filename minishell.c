/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:43:42 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/21 01:29:22 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_bulletin_2(char **ptr)
{
	if (ft_strcmp(ptr[0], "pwd") == 0)
		return (ft_pwd(ptr), 1);
	if (ft_strcmp(ptr[0], "exit") == 0)
		return (ft_exit(ptr), 1);
	else if (ft_strcmp(ptr[0], "echo") == 0)
		return (ft_echo(ptr), 1);
	else if (ft_strcmp(ptr[0], "cd") == 0)
		return (ft_cd(ptr), 1);
	else if (ft_strcmp(ptr[0], "env") == 0)
		return (ft_env(), 1);
	else if (ft_strcmp(ptr[0], "unset") == 0)
		return (ft_unset_more_then_one(ptr), 1);
	else if (ft_strcmp(ptr[0], "export") == 0)
	{
		if (!ptr[1])
			return (only_export(), 1);
		return (ft_export(ptr), 1);
	}
	return (0);
}
int	ft_bulletin(char *cmd)
{
	t_pipe	*lst_of_args;
	t_redic	*lst_of_red;
	char	**ptr;

	lst_of_args = NULL;
	lst_of_red = NULL;
	ft_get_args_and_red(cmd, &lst_of_args, &lst_of_red);
	if (lst_of_red)
		run_rediction(lst_of_red);
	if (!lst_of_args)
		return (0);
	ptr = args_lst_to_tab(lst_of_args);
	ft_convert_to_lower(ptr[0]);
	return (ft_bulletin_2(ptr));
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

char	*get_unique_name(void)
{
	static int	nb;

	return (ft_strjoin("/tmp/here_file_", ft_itoa(nb++)));
}

int	here_loop(t_lexm *tmp, char *file_name, int fd)
{
	char		*line;

	line = readline("> ");
	add_garbage(line);
	if (!line || ft_strcmp(tmp->next->cmd, line) == 0 || g_var.doc)
	{
		tmp->cmd = "<";
		tmp->next->cmd = file_name;
		close (fd);
		return (1);
	}
	write (fd, ft_strjoin(line, "\n"), ft_strlen(line) + 1);
	return (0);
}

void	main_heredoc(t_lexm **lexer)
{
	char		*file_name;
	t_lexm		*tmp;
	int			fd;

	tmp = *lexer;
	while (tmp && !g_var.doc)
	{
		if (tmp->type == HEREDOC)
		{
			file_name = get_unique_name();
			fd = open(file_name, O_RDWR | O_CREAT, 0666);
			while (1)
			{
				if (here_loop(tmp, file_name, fd))
					break ;
			}
		}
		tmp = tmp->next;
	}
}

void	handler(int sig)
{
	(void)sig;
	g_var.doc = 1;
	rl_done = 1;
}

int	event(void)
{
	return (0);
}

void	ft_run_heredoc(t_lexm **lexer)
{
	g_var.doc = 0;
	signal(SIGINT, handler);
	rl_event_hook = event;
	main_heredoc(lexer);
}

char	*check_heredoc(char *cmd)
{
	t_lexm	*here;

	here = ft_lexer(cmd);
	ft_run_heredoc(&here);
	return (lexter_to_string(here));
}

void	pass_or_not(char *cmd)
{
	cmd = check_heredoc(cmd);
	if (g_var.doc == 1)
		g_var.doc = 0;
	else
		ft_pipe(cmd);
}

void	ft_start(int fd[2])
{
	char	*cmd;

	while (1)
	{
		g_var.doc = 0;
		cmd = readline("FRATELLO😈=> ");
		add_garbage(cmd);
		if (!cmd)
			break ;
		if (cmd[0] == '\0' || only_space(cmd))
			continue ;
		add_history(cmd);
		if (ft_syntax_general(cmd) == 1)
		{
			cmd = check_heredoc(cmd);
			ft_putstr_fd("\033[31mMinishell : syntax error !!!\n\033[37m", 2);
		}
		else
			pass_or_not(cmd);
		dup2(fd[0], 0);
		dup2(fd[1], 1);
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	(void)av;
	if (ac == 1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		g_var.garbage = NULL;
		ft_new_env(env);
		ft_start(fd);
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
