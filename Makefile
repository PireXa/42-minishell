# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 10:31:48 by rdas-nev          #+#    #+#              #
#    Updated: 2022/09/23 13:34:29 by fde-albe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		main/main.c main/sighandler.c main/prompt.c \
					builtins/builtins.c builtins/cd_pwd.c builtins/echo.c builtins/exit.c \
					builtins/export.c builtins/export_utils.c  builtins/export_utils2.c \
					builtins/export_utils3.c builtins/unset.c \
					exec/children.c exec/commandsmaster.c exec/gnl.c exec/gnl_utils.c \
					exec/pipex.c exec/pipex_utils.c exec/quadpointer.c \
					parser/parser.c parser/parser2.c parser/parser3.c parser/parser4.c \
					parser/parser5.c parser/parser6.c parser/parser7.c parser/parser8.c \
					utils/ft_strncmp.c utils/listfuncs.c utils/split.c utils/split2.c \
					utils/ft_calloc.c \
					redirects/chidren.c redirects/ft_memcmp.c redirects/ft_strhr.c \
					redirects/ft_substr.c redirects/heredoc.c redirects/pipex_bonus.c \
					redirects/pipex_utils.c redirects/ft_caloc.c redirects/ft_spit.c \
					redirects/ft_stjoin.c redirects/ft_strlen.c redirects/ft_stdup.c \
					redirects/gnl.c redirects/gnl_utils.c redirects/redirections.c \

OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror #-fsanitize=address
RM			=		rm -f

NAME		= 		minishell

objs/%.o: srcs/%.c
			@mkdir -p objs
			@mkdir -p objs/builtins
			@mkdir -p objs/exec
			@mkdir -p objs/parser
			@mkdir -p objs/utils
			@mkdir -p objs/main
			@mkdir -p objs/redirects
			@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
			@cc $(OBJS) $(CFLAGS) -o $(NAME) -lreadline

all:      	$(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)  

re:         fclean all
