## Main script for batch testing 

## Batch execution of several scenarios, 
## add more with the new code.

## Add new code, add here a working example

echo " -> Compiling minishell"
make 
echo " -> Running different tests"

./minishell -c "echo hola"

./minishell -c "echo"

./minishell -c "env"

## Comando que falla, lo silenciamos
./minishell -c "${HOME}" || true

./minishell -c "cd"
./minishell -c "cd \${HOME}"
./minishell -c "echo \${HOME}"
./minishell -c "pwd"
./minishell -c "export A=5"
./minishell -c "B=8"
./minishell -c "echo \${HOME}/dir"
## Comando que falla, lo silenciamos
./minishell -c "  \"hola\"  echo|hel*lo  " || true


## Estos valgrind solo muestran algo si hay errores.
valgrind \
		--leak-check=full --show-leak-kinds=all --log-file=/dev/null \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		./minishell -c "echo ${HOME}"

valgrind \
		--leak-check=full --show-leak-kinds=all --log-file=/dev/null \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		./minishell -c "cd ${HOME}"

valgrind \
		--leak-check=full --show-leak-kinds=all --log-file=/dev/null \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		./minishell -c "env"

valgrind \
		--leak-check=full --show-leak-kinds=all --log-file=/dev/null \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		./minishell -c "git status"


echo " -> Cleanup"
make fclean > /dev/null
