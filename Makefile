# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matef <matef@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 15:37:33 by skasmi            #+#    #+#              #
#    Updated: 2022/10/18 23:13:15 by matef            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror

READLINE = $(shell brew --prefix readline)

INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)

NAME=minishell
NAME2=minishell.h

SRCS=	minishell.c \
		libft/ft_lst_addback_env.c \
		libft/ft_isalnum.c \
		libft/ft_isalpha.c \
		libft/ft_lst_last_env.c \
		libft/ft_lstnew_env.c \
		libft/ft_split.c \
		libft/ft_itoa.c \
		libft/ft_strcpy.c \
		libft/ft_strlen.c \
		libft/ft_strcmp.c \
		libft/ft_strchr.c \
		libft/ft_atoi.c \
		libft/ft_memmove.c \
		libft/ft_strjoin.c \
		libft/ft_substr.c \
		libft/ft_strdup.c \
		libft/ft_memcpy.c \
		libft/ft_putstr_fd.c \
		libft/ft_strnstr.c \
		builtins/env.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/cd.c \
		builtins/exit.c \
		builtins/final.c \
		builtins/unset.c \
		builtins/echo.c \
		src/syntax_error.c \
		src/syntax_error2.c \
		src/syntax_error_general.c \
		src/ft_pipe.c \
		src/lst_pipe.c \
		src/execution.c \
		utils.c \
		src/redirection.c \
		src/open_files.c \
		src/heredoc.c\
		src/garbage.c\
		src/expand.c


BOBJCTS=$(BSRCS:%.c=%.o)

OBJCTS=$(SRCS:%.c=%.o)

$(NAME) : $(OBJCTS) $(NAME2)

		$(CC) $(CFLAGS) -I $(INCLUDE_READLINE) -L $(LIB_READLINE) -lreadline $(OBJCTS) -o $(NAME)
				
		@echo "\033[90m███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\033[0m" 
		@echo "\033[90m████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\033[0m"
		@echo "\033[91m██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\033[0m"
		@echo "\033[91m██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░ \033[0m"
		@echo "\033[93m██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗ \033[0m"
		@echo "\033[93m╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\033[0m"

%.o: %.c minishell.h
	cc $(flags) -I $(INCLUDE_READLINE) -c $< -o $@

all: $(NAME)
	
clean:
				rm -f $(OBJCTS) $(BOBJCTS)

fclean: clean
				rm -f $(NAME)

re: fclean all