/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <skasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:43:42 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/20 21:11:29 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_run_heredoc(t_lexm **lexer)
{
	t_lexm		*tmp;
	char		*line;
	int			fd;
	static int	nb;
	char		*file_name;

	tmp = *lexer;
	g_var.doc = 0;
	signal(SIGINT, handler);
	rl_event_hook = event;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			file_name = ft_strjoin("/tmp/here_file_", ft_itoa(nb++));
			fd = open(file_name, O_RDWR | O_CREAT, 0666);
			while (1)
			{
				line = readline("> ");
				add_garbage(line);
				if (!line || ft_strcmp(tmp->next->cmd, line) == 0 || g_var.doc)
				{
					tmp->cmd = "<";
					tmp->next->cmd = file_name;
					close(fd);
					break ;
				}
				write(fd, ft_strjoin(line, "\n"), ft_strlen(line) + 1);
			}
		}
		tmp = tmp->next;
	}
}

t_lexm	*ft_lexer(char *cmd)
{
	int		i;
	char	qouts;
	char	*to_expand;
	t_lexm	*lexer;

	i = 0;
	to_expand = ft_strdup("");
	lexer = NULL;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == '\'' || cmd[i] == '\"')
			{
				qouts = cmd[i];
				to_expand = ft_strjoin(to_expand, ft_substr(cmd, i, 1));
				i++;
				while (cmd[i] && cmd[i] != qouts)
				{
					to_expand = ft_strjoin(to_expand, ft_substr(cmd, i, 1));
					i++;
				}
				to_expand = ft_strjoin(to_expand, ft_substr(cmd, i, 1));
				i++;
			}
			else
			{
				if (cmd[i] != '>' && cmd[i] != '<' && cmd[i] != '|')
					to_expand = ft_strjoin(to_expand, ft_substr(cmd, i, 1));
				else
				{
					if (to_expand[0] != '\0')
					{
						add_to_lexer(&lexer, to_expand);
						to_expand = ft_strdup("");
					}
					if (cmd[i + 1] == cmd[i])
					{
						add_to_lexer(&lexer, ft_substr(cmd, i, 2));
						i++;
					}
					else
						add_to_lexer(&lexer, ft_substr(cmd, i, 1));
				}
				i++;
			}
		}
		if (to_expand[0] != '\0')
		{
			add_to_lexer(&lexer, to_expand);
			to_expand = ft_strdup("");
		}
		i++;
	}
	return (lexer);
}

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	int		fd[2];
	t_lexm	*here;

	fd[0] = dup(0);
	fd[1] = dup(1);
	*env = NULL;
	(void)av;
	if (ac == 1)
	{
		g_var.garbage = NULL;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sig);
		ft_new_env(env);
		while (1)
		{
			here = NULL;
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
				here = ft_lexer(cmd);
				ft_run_heredoc(&here);
				cmd = lexter_to_string(here);
				ft_putstr_fd("Minishell : syntax error !!!\n", 2);
			}
			else
			{
				here = ft_lexer(cmd);
				ft_run_heredoc(&here);
				cmd = lexter_to_string(here);
				if (g_var.doc == 1)
					g_var.doc = 0;
				else
					ft_pipe(cmd);
			}
			dup2(fd[0], 0);
			dup2(fd[1], 1);
			// free_garbage();
		}
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
