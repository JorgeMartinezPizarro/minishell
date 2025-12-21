# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2025/12/21 14:00:14 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft

LIBFT=$(LIBFT_DIR)/libft.a

## TODO: descomentar los ultimos dos ficheros
## cuando por fin funcionen.
## En el main_tmp hay un codigo preparado para usar
## ambas cuando por fin compile y este terminado.
FILES = execution/run_built_in main \
	environ/expand_vars environ/extract_variables \
	environ/environments environ/environments2 \
	environ/environments3 \
	execution/run_program wildcard/expand_wildcard \
	tokenizer/token_utils tokenizer/tokenizer \
	wildcard/expand_tokens utils/free_str_array \
	utils/free execution/run_built_in_utils \
	utils/join_paths execution/run_cd execution/run_echo \
	parser/parser_utils parser/parser parser/tree_utils ## \
	execution/redirections execution/execute_tree

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
	echo "\n Total of lines: $$lines"; \
	files=$$(git ls-files | wc -l); \
	echo " Total of files: $$files\n"

.PHONY = test
