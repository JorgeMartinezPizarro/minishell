#!/bin/bash

OK="\033[1;32mOK\033[0m "
KO="\033[1;31mKO\033[0m "

VALGRIND="valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet"

validate_norm()
{
    norm_out=$(norminette "$1" | grep -v locale || true)
	files=$(find $1 -type f | wc -l)
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

test_command()
{
    COMMAND="$1"
    OUTPUT=$(./minishell -c "$COMMAND" 2>/dev/null)
    EXIT_CODE=$?
    EXPECTED=$(bash -c "$COMMAND" 2>/dev/null)
    EXPECTED_EXIT=$?
	if [[ "$OUTPUT" == "$EXPECTED" && $EXIT_CODE -eq $EXPECTED_EXIT ]]; then
		echo -ne "$OK"
	else
		echo -ne "$KO"
		echo -e "\nCommand: $COMMAND"
		if [[ "$OUTPUT" != "$EXPECTED" ]]; then
			echo -e "\nExpected output:\n$EXPECTED"
			echo -e "\nGot output:\n$OUTPUT"
		fi
		if [[ $EXIT_CODE -ne $EXPECTED_EXIT ]]; then
			echo -e "\nExpected exit code: $EXPECTED_EXIT"
			echo -e "Got exit code: $EXIT_CODE"
		fi
	fi
}

echo -ne " -> Running norminette.\n\n "

validate_norm ./srcs
validate_norm ./includes
validate_norm ./libft

echo -ne "\n\n -> Exit code validation.\n\n "

test_command "echo hola"
test_command "echo"
test_command "export | grep -v SHLVL | grep -v ' _='"
test_command "${HOME}"
test_command "cd"
test_command "cd \${HOME}"
test_command "echo \${HOME}"
test_command "pwd"
test_command "export A=5"
test_command "export B=8"
test_command "echo \${HOME}/dir"
test_command "  \"hola\"  echo|hel*lo  "
test_command "echo hola && echo adios"
test_command "(echo hola) && echo adios"
test_command "(cd r || echo fail 1 && cd x) || echo fail 2"
test_command "(echo hola | grep h) && (echo mundo || echo falló)"
test_command '(ls | grep txt) || (echo "no hay txt" && echo "fin")'
test_command '(echo 1 && echo 2) | (grep 2 || echo "no se encontró 2")'
test_command "(echo start && false) || (echo retry | grep r && echo done)"

echo -ne "\n\n -> Testing memory leaks.\n\n "

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
$VALGRIND ./minishell -c "a=15 export | grep -v 'hola'" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "( echo L1 && ( echo L2 && ( echo L3 && ( echo L4 ) ) ) )" > /dev/null && echo -ne "$OK"
$VALGRIND ./minishell -c "( echo X && ( echo Y && ( false && ( echo Z ) ) ) )" > /dev/null && echo -ne "$OK"

## Test para el shebang de minishell.
export PATH="$PATH:$PWD"
$VALGRIND ./minishell -c ./tests/run.sh > /dev/null && echo -ne "$OK"

echo -ne "\n\n -> Not interactive usage.\n\n "

echo "cd srcs && cd .. && cd srcs && cd .. && cd s*" | ./minishell && echo -ne "$OK"
echo "./minishell -c 'echo \$MSHLVL'" | ./minishell > /dev/null && echo -ne "$OK"

echo -ne "\n\n -> Command comparison.\n\n "

test_command "(echo hola) && echo adios"
test_command "( echo L1 && ( echo L2 && ( echo L3 && ( echo L4 ) ) ) )"
test_command "echo hola && (echo adios)"
test_command "( echo A && ( false || ( echo B && ( echo C || echo D ) ) ) )"
test_command "echo hola && echo adios"
test_command "cd .. && echo hola && cd - && echo $PWD"
test_command "echo hola'adios'"
test_command "echo hola'$HOME'"
test_command "echo $PWD && cd .. && cd - && echo $PWD"
test_command "A=150 env | grep -v '^MSHLVL' | grep -v '^SHLVL' | grep -v '^_=' | sort"
test_command "((echo a && echo b) || (echo c && echo d))"
test_command "((cd r && echo b) || (echo c && echo d))"
test_command "cd unknown && unnamed"
test_command "mkdir"
test_command "touch hola && rm -f hola"
test_command "echo hola > tmpfile && cat tmpfile && rm -f tmpfile"
test_command "echo hola > tmpfile && echo adios >> tmpfile && cat tmpfile && rm -f tmpfile"
test_command "echo 'hola' > tmpfile && cat < tmpfile && rm -f tmpfile"
test_command "( echo X && ( echo Y && ( false && ( echo Z ) ) ) )"

echo -e "\n"