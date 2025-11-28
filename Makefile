# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2025/11/28 01:02:13 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft

LIBFT=$(LIBFT_DIR)/libft.a

# Finish the makefile: `bonus` `clean` and `re`.

FILES = main.c

SRCS     = $(addprefix src/, $(FILES))

OBJS = $(SRCS:.c=.o)

CC       = cc

CFLAGS   = -Wall -Wextra -Werror \
	-I./$(SRC_DIR) -I./$(LIBFT_DIR)/src

all: $(NAME)

${NAME}: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) \
		-L./$(LIBFT_DIR) -lft -o minishell

$(LIBFT):
	make -C $(LIBFT_DIR)

fclean:
	make -C libft fclean
	rm -f $(OBJS)
	rm -f minishell

run: all
	./minishell
	