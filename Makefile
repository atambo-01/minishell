# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atambo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:48:12 by atambo            #+#    #+#              #
#    Updated: 2025/01/15 14:35:27 by atambo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS		=	-g #-Wall -Wextra -Werror
NAME		=	minishell
OBJS		=	$(SOURCES:.c=.o)
INCLUDES	=	-Iincludes

SOURCES		=	src/main.c\
				src/parsing.c\
				src/parsing_plus.c\
				src/ft_pwd.c\
				src/get_cmd.c\

OBJS		=	$(SOURCES:.c=.o)
INCLUDES	=	-Iinc -Ilibft

SUBDIR		=	inc/libft
LIBS		=	-lreadline -lncurses inc/libft/libft.a

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

