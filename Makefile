# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2025/11/28 00:45:43 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT=libft/libft.a

# Finish the makefile

all: $(NAME)

${NAME}: $(LIBFT)
	cc -Ilibft/src src/main.c -Llibft -lft -o minishell
$(LIBFT):
	make -C libft

fclean:
	make -C libft fclean
	rm -f minishell

run: all
	./minishell
	