# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atambo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:48:12 by atambo            #+#    #+#              #
#    Updated: 2025/03/22 12:50:16 by atambo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-g -Wall -Wextra -Werror
NAME		=	minishell
OBJS		=	$(SOURCES:.c=.o)
INCLUDES	=	-Iincludes

SOURCES		=	src/main.c\
				src/parsing.c\
				src/parsing_aux.c\
				src/parsing_plus.c\
				src/get_cmd.c\
				src/get_cmd_aux.c\
				src/pipe.c\
				src/get_subtoken.c\
				src/utils.c\
				src/expand.c\
				src/expand_aux.c\
				src/env_list.c\
				src/aux_env_list.c\
				src/aux2_env_list.c\
				src/execute.c\
				src/builtins.c\
				src/aux_builtins.c\
				src/env.c\
				src/export.c\
				src/signal_handlers.c\
				src/signal_handlers_2.c\
				src/signal.c\
				src/ft_unset.c\
				src/redir.c\
				src/redir_heredoc.c\
				src/redir_utils.c\
				src/main_functions.c\
				src/main_auxiliary.c\
				src/aux_exit.c\
				src/exit.c\
				src/exit_atoi.c\
				src/ft_get_path.c\
				src/pipe_aux.c\

OBJS		=	$(SOURCES:.c=.o)
INCLUDES	=	-Iinc -Ilibft

SUBDIR		=	./libft
LIBS		=	-lreadline  ./libft/libft.a

all: submake $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBS) -lreadline -lncurses

submake:
	$(foreach dir, $(SUBDIR), $(MAKE) -C $(dir);)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@

clean:
	rm -f $(OBJS)
	$(foreach dir, $(SUBDIR), $(MAKE) -C $(dir) clean;)

fclean: clean
	rm -f $(NAME)
	$(foreach dir, $(SUBDIR), $(MAKE) -C $(dir) fclean;)

re: fclean all

# Phony targets
.PHONY: all clean fclean re submake

