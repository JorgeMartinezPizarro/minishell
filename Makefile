# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2025/12/22 23:20:25 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft

LIBFT=$(LIBFT_DIR)/libft.a

FILES = execution/run_built_in main \
	environ/expand_vars environ/extract_variables \
	environ/environments environ/environments2 \
	environ/environments3 \
	execution/run_program wildcard/expand_wildcard \
	tokenizer/token_utils tokenizer/tokenizer \
	wildcard/expand_tokens utils/free_str_array \
	utils/free execution/run_built_in_utils \
	utils/join_paths execution/run_cd execution/run_echo \
	parser/parser_utils parser/parser parser/tree_utils  \
	execution/redirections execution/execute_tree \
	execution/pipes wildcard/expand_env_tokens

## TODO: crear bonus target with some new files _bonus

OBJECTS = $(addprefix srcs/, $(FILES:=.o))

CC       = cc

CFLAGS   = -Wall -Wextra -Werror \
	-I./includes -I./$(LIBFT_DIR)/src -g

all: $(NAME)

${NAME}: $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) \
		-lreadline -L./$(LIBFT_DIR) -lft -o minishell

$(LIBFT):
	make -C $(LIBFT_DIR)

re: fclean all

test: fclean
	@./tests/test.sh

## Run minishell with valgrind. readline.supp suppress all LEAKS
## from readline. All supp rules are readline or add_history 
## usage.
run: all
	valgrind \
		--leak-check=full --show-leak-kinds=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		./minishell
clean:
	make -C libft clean
	rm -f $(OBJECTS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

stats:
	@lines=$$( \
		{ \
			find srcs includes -type f \( -name '*.c' -o -name '*.h' -o -name '*.sh' \) -exec cat {} +; \
		} | grep -Ev '^[[:space:]]*(#|//|$$)' | wc -l \
	); \
	echo ""; \
	echo "Total of lines: $$lines"; \
	files=$$( \
		find srcs includes -type f \( -name '*.c' -o -name '*.h' -o -name '*.sh' \) | wc -l \
	); \
	echo "Total of files: $$files"; \
	echo ""

.PHONY = test
