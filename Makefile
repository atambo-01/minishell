# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atambo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:48:12 by atambo            #+#    #+#              #
#    Updated: 2024/12/12 18:50:37 by atambo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
NAME		=	minishell
OBJS		=	$(SOURCES:.c=.o)
INCLUDES	=	-Iincludes

SOURCES		=	src/main.c src/builtings.c src/pipe.c

OBJS		=	$(SOURCES:.c=.o)
INCLUDES	=	-Iincludes

SUBDIR		=	

all: submake $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) -lreadline -lncurses

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

