# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2025/12/12 05:29:51 by maanguit         ###   ########.fr        #
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

MY_LIST = utils/run_command jorges_main \
	environ/expand_vars environ/extract_variables \
	environ/environments utils/join_paths

OBJETOS = $(addprefix srcs/, $(MY_LIST:=.o))

$(NOMBRE): $(LIBFT) $(OBJETOS)
	$(CC) $(CFLAGS) $(OBJETOS) -Llibft -lft -o $(NOMBRE)

test:
	@./tests/test.sh
	
clean:
	make -C libft clean
	rm -f $(OBJS) $(OBJETOS)

fclean: clean
	make -C libft fclean
	rm -f $(NOMBRE)
	rm -f minishell

token:
	@make -C libft -s
	@cc srcs/tokenizer/token_utils.c srcs/tokenizer/tokenizer.c libft/libft.a -Wall -Wextra -Werror -g
	@./a.out "  \"hola\"  echo | hel*lo  "
	@echo "next test:\n"
	@./a.out "ls -l /tmp"
	@echo "next test:\n"
	@./a.out "echo 'hola mundo' "user $USER""

tclean:
	make fclean -C libft
	rm a.out

.PHONY = test