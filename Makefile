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

SRCS		=		main.c sighandler.c commandsmaster.c builtins.c ft_strncmp.c \
					listfuncs.c builtins_export_utils.c split.c unset.c  \
					pipex/children.c pipex/ft_memcmp.c pipex/get_next_line.c \
					pipex/get_next_line_utils.c pipex/heredoc.c parser.c \
					pipex/pipex.c pipex/pipex_utils.c export.c \

OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror
RM			=		rm -f

NAME		= 		minishell

objs/%.o: srcs/%.c
			@mkdir -p objs
			@mkdir -p objs/pipex
			@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
			@cc $(OBJS) $(CFLAGS) -o $(NAME) -lreadline

all:      	$(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)  

re:         fclean all
