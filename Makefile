# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 00:27:12 by jomarti3          #+#    #+#              #
#    Updated: 2025/12/25 16:33:17 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft

LIBFT=$(LIBFT_DIR)/libft.a

FILES = \
	builtins/run_built_in main builtins/run_built_in_utils \
	builtins/run_cd builtins/run_echo builtins/run_export \
	builtins/run_assign \
	environ/extract_variables \
	environ/environments environ/environments2 \
	environ/environments3 environ/print_sorted_env \
	tokenizer/token_utils tokenizer/tokenizer \
	expanse/expand_wildcard_tokens expanse/expand_wildcard \
	expanse/expand_env_tokens expanse/expand_vars \
	utils/free2 utils/free utils/join_paths \
	parser/parser_utils parser/parser parser/tree_utils  \
	execution/redirections execution/execute_tree \
	execution/pipes execution/run_program \
	execution/run_program_utils \
	signals/signal_utils utils/get_prompt

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

clean:
	make -C libft clean
	rm -f $(OBJECTS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

## Ejecuta el script de tests con todos los tests
## TODO: terminar los tests
test: all
	@./tests/test.sh

## Run minishell with valgrind. readline.supp suppress all LEAKS
## from readline. All supp rules are readline or add_history 
## usage.
run: all
	valgrind \
		--leak-check=full --show-leak-kinds=all \
		--gen-suppressions=all \
		--suppressions=readline.supp \
		--errors-for-leak-kinds=all \
		./minishell

## Estadisticas del proyecto
stats:
	@lines=$$( \
		{ \
			find srcs includes -type f \( -name '*.c' -o -name '*.h' -o -name '*.sh' \) -exec cat {} +; \
		} | grep -Ev '^[[:space:]]*(#|//|$$)' | wc -l \
	); \
	echo ""; \
	echo "  - Total of lines: \033[0;32m$$lines\033[0m"; \
	files=$$( \
		find srcs includes -type f \( -name '*.c' -o -name '*.h' -o -name '*.sh' \) | wc -l \
	); \
	echo "  - Total of files: \033[0;32m$$files\033[0m"; \
	echo ""

## Comando para visualizar minishells anidadas
## en otra shell abre minishells anidadas para verlo
view:
	@watch -n 1 "ps -ef --forest | grep minishell | grep -v grep"
.PHONY = test
