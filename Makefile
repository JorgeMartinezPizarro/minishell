# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2025/12/09 22:32:09 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft

LIBFT=$(LIBFT_DIR)/libft.a

FILES = main.c parse_command.c

FILES_BONUS = main.c parse_command.c

SRCS     = $(addprefix src/, $(FILES))

OBJS = $(SRCS:.c=.o)

SRCS_BONUS     = $(addprefix src/, $(FILES_BONUS))

OBJS_BONUS = $(SRCS:.c=.o)

CC       = cc

CFLAGS   = -Wall -Wextra -Werror \
	-I./includes -I./$(LIBFT_DIR)/src

all: $(NAME)

${NAME}: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) \
		-L./$(LIBFT_DIR) -lft -o minishell

$(LIBFT):
	make -C $(LIBFT_DIR)

re: fclean all

run: all
	./minishell


## TEMPORARY COMMANDS JORGE
NOMBRE = jorge

MY_LIST = run_command jorges_main

OBJETOS = $(addprefix srcs/, $(MY_LIST:=.o))

$(NOMBRE): $(LIBFT) $(OBJETOS)
	$(CC) $(CFLAGS) $(OBJETOS) -Llibft -lft -o $(NOMBRE)

test: jorge
	./jorge "echo hola"
	./jorge "echo" || true
	./jorge "env"
	
clean:
	make -C libft clean
	rm -f $(OBJS) $(OBJETOS)

fclean: clean
	make -C libft fclean
	rm -f $(NOMBRE)
	rm -f minishell

