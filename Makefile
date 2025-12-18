# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2025/12/14 21:13:29 by maanguit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft

LIBFT=$(LIBFT_DIR)/libft.a

## TODO: merge jorges_main.c and main.c
FILES = utils/run_built_in jorges_main \
	environ/expand_vars environ/extract_variables \
	environ/environments utils/join_paths \
	utils/run_program utils/expand_wildcard \
	tokenizer/token_utils tokenizer/tokenizer \
	utils/expand_tokens utils/free_str_array \
	utils/free

## TODO: crear bonus target with some new files _bonus

OBJECTS = $(addprefix srcs/, $(FILES:=.o))

CC       = cc

CFLAGS   = -Wall -Wextra -Werror \
	-I./includes -I./$(LIBFT_DIR)/src

all: $(NAME)

${NAME}: $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) \
		-lreadline -L./$(LIBFT_DIR) -lft -o minishell

$(LIBFT):
	make -C $(LIBFT_DIR)

re: fclean all

run-tests:
	@./tests/tests.sh
	
clean:
	make -C libft clean
	rm -f $(OBJECTS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

token:
	@make -C libft -s
	@cc srcs/tokenizer/token_utils.c srcs/tokenizer/tokenizer.c libft/libft.a -Wall -Wextra -Werror -g
	@./a.out "  \"hola\"  echo|hel*lo  "
	@echo "next test:\n"
	@./a.out "ls -l /tmp"
	@echo "next test:\n"
	@./a.out "echo 'hola mundo' "user $USER""

tclean:
	make fclean -C libft
	rm a.out

stats:
	@lines=$$( \
		{ \
			cat Makefile; \
			find includes srcs -type f \( -name '*.c' -o -name '*.h' -o -name '*.sh' \) -exec cat {} +; \
		} | grep -Ev '^\s*(#|//|$$)' | wc -l \
	); \
	echo "Total lines: $$lines"

.PHONY = tests
