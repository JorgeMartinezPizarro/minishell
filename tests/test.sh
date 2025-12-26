#!/bin/bash

OK="\033[1;32mOK\033[0m "
KO="\033[1;31mKO\033[0m "

VALGRIND="valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet"

validate_norm(){
    
    # Ejecutar norminette, capturar stdout y stderr
    norm_out=$(norminette "$1" | grep -v locale || true)
	files=$(find $1 -type f | wc -l)
    # Contar cuántas veces aparece "Error:"
    error_count=$(echo "$norm_out" | grep -c "Error:" || true)

    if [ "$error_count" -ne 0 ]; then
		norminette "$1" | head -n40
        echo -ne "$KO"
        return 1
    else
        echo -ne "$OK"
        return 0
    fi
}

test_command() {
	# Usamos timeout por si algun comando se atasca.
	COMMAND="$1"
	OUTPUT=$(timeout 1s ./minishell -c "$COMMAND" 2>/dev/null) 
	EXIT_CODE=$?

	EXPECTED=$(bash -c "$COMMAND")

	if [[ $EXIT_CODE -ne 0 ]]; then
		echo -ne "$KO"
		echo -e "\n\n Command: \n $COMMAND "
		echo -e "\n\n The command did not finish properly."
		echo -e "\n Expected:\n $EXPECTED\n Got:\n $OUTPUT"
	else
		if [[ "$OUTPUT" == "$EXPECTED" ]]; then
			echo -ne "$OK"
		else
			echo -ne "$KO"
			echo -e "\n Expected:\n $EXPECTED\n Got:\n $OUTPUT"
		fi
	fi
}

echo -ne " -> Running norminette\n\n "

validate_norm ./srcs
validate_norm ./includes
validate_norm ./libft

echo -ne "\n\n -> Running different tests\n\n "

./minishell -c "echo hola" > /dev/null && echo -ne "$OK"
./minishell -c "echo" > /dev/null && echo -ne "$OK"
./minishell -c "export" > /dev/null && echo -ne "$OK"
./minishell -c "${HOME}"  > /dev/null 2>&1 || echo -ne "$OK"
./minishell -c "cd" > /dev/null && echo -ne "$OK"
./minishell -c "cd \${HOME}" > /dev/null && echo -ne "$OK"
./minishell -c "echo \${HOME}" > /dev/null && echo -ne "$OK"
./minishell -c "pwd" > /dev/null && echo -ne "$OK"
./minishell -c "export A=5" > /dev/null && echo -ne "$OK"
./minishell -c "export B=8" > /dev/null && echo -ne "$OK"
./minishell -c "echo \${HOME}/dir" > /dev/null && echo -ne "$OK"
./minishell -c "  \"hola\"  echo|hel*lo  "  > /dev/null 2>&1 || echo -ne "$OK"

echo -ne "\n\n -> Testing memory leaks\n\n "

$VALGRIND ./minishell -c "echo ${HOME}" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "export" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "a=15 b=17" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "cd ${HOME}" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "env" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "git status" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "echo hola && echo adios" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "git ls-files | grep \"\.c\"" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "(echo hola) && echo adios || echo que" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "echo hola && (echo adios)" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "echo hola adios | grep hola" > /dev/null && echo -ne "$OK"

## Test para el shebang de minishell.
export PATH="$PATH:$PWD"
$VALGRIND ./minishell -c ./tests/run.sh > /dev/null && echo -ne "$OK"

./minishell -c "echo hola && echo adios" > /dev/null && echo -ne "$OK"
./minishell -c "(echo hola) && echo adios" > /dev/null && echo -ne "$OK"
./minishell -c "(cd r || echo fail 1 && cd x) || echo fail 2" > /dev/null 2>&1 && echo -ne "$OK"

echo -ne "\n\n -> Some additional tests\n\n "

echo "cd srcs && cd .. && cd srcs && cd .. && cd s*" | ./minishell && echo -ne "$OK"
echo "./minishell -c 'echo \$MSHLVL'" | ./minishell > /dev/null && echo -ne "$OK"


test_command "(echo hola) && echo adios"
test_command "(echo hola) && (echo adios)"
test_command "echo hola && (echo adios)"
test_command "echo hola && echo adios"
test_command "cd .. && echo hola && cd - && echo $PWD"
test_command "echo hola'adios'"
test_command "echo hola'$HOME'"
test_command "echo $PWD && cd .. && cd - && echo $PWD"
test_command "A=150 export | grep -v 'MSHLVL' | grep -v ' _='"

echo -e "\n"