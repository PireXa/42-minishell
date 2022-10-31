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

SRCS		=		main.c sighandler.c \
					builtins/builtins.c builtins/cd_pwd.c builtins/echo.c builtins/exit.c \
					builtins/export.c builtins/export_utils.c builtins/unset.c \
					exec/children.c exec/commandsmaster.c exec/gnl.c exec/gnl_utils.c \
					exec/pipex.c exec/pipex_utils.c \
					parser/parser.c parser/parser2.c\
					utils/ft_strncmp.c utils/listfuncs.c utils/split.c \

OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror
RM			=		rm -f

NAME		= 		minishell

objs/%.o: srcs/%.c
			@mkdir -p objs
			@mkdir -p objs/builtins
			@mkdir -p objs/exec
			@mkdir -p objs/parser
			@mkdir -p objs/utils
			@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
			@cc $(OBJS) $(CFLAGS) -o $(NAME) -lreadline

all:      	$(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)  

re:         fclean all
