#!/bin/bash

### Use bash to validate exit code
### of commands and diff for results

echo " -> Running different tests"

./minishell -c "echo hola" > /dev/null

./minishell -c "echo" > /dev/null

./minishell -c "export" > /dev/null

## Comando que falla, lo silenciamos
./minishell -c "${HOME}"  > /dev/null || true

./minishell -c "cd" > /dev/null
./minishell -c "cd \${HOME}" > /dev/null
./minishell -c "echo \${HOME}" > /dev/null
./minishell -c "pwd" > /dev/null
./minishell -c "export A=5" > /dev/null
./minishell -c "export B=8" > /dev/null
./minishell -c "echo \${HOME}/dir" > /dev/null
## Comando que falla, lo silenciamos
./minishell -c "  \"hola\"  echo|hel*lo  "  > /dev/null || true

echo "Testing memory leaks of built ins"
## Probamos que no haya leaks en varios comandos 
valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "echo ${HOME}" > /dev/null

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "cd ${HOME}" > /dev/null

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "env" > /dev/null

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "git status" > /dev/null

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell ./tests/run.sh > /dev/null

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./tests/run.sh > /dev/null

./minishell -c "echo hola && echo adios"

./minishell -c "(echo hola) && echo adios"

./minishell -c "(cd r || echo fail 1 && cd x) || echo fail 2"

## Probamos que MSHLVL sube a 2.
echo "./minishell -c 'echo \$MSHLVL'" | ./minishell

## Ejecutamos un fichero directamente
./minishell ./tests/run.sh

## Ejecutamos el comando desde shell 
./minishell -c ./tests/run.sh