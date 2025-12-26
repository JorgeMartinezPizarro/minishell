#!/bin/bash

OK="\033[1;32mOK\033[0m "
KO="\033[1;31mKO\033[0m "

VALGRIND="valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=tests/readline.supp --errors-for-leak-kinds=all \
		--quiet"

validate_norm()
{
    norm_out=$(norminette "$1" | grep -v locale || true)
	files=$(find $1 -type f | wc -l)
    error_count=$(echo "$norm_out" | grep -c "Error:" || true)
    if [ "$error_count" -ne 0 ]; then
		norminette "$1" | head -n40
        echo -ne "\n$KO"
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
		echo -ne "\n$KO"
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

test_leaks()
{
	$VALGRIND ./minishell -c "$1" > /dev/null && echo -ne "$OK"
}


echo -ne " -> Running norminette.\n\n "

validate_norm ./srcs
validate_norm ./includes
validate_norm ./libft

echo -ne "\n\n -> Test simple commands.\n\n "

test_command "echo hola"
test_command "echo"
test_command "export | grep -v SHLVL | grep -v ' _='"
test_command "export a && export | grep -v SHLVL | grep -v ' _='"
test_command "export a && env | grep -v SHLVL | grep -v '^_=' | sort"
test_command "export a= && export | grep -v SHLVL | grep -v ' _='"
test_command "export a= && env | grep -v SHLVL | grep -v '^_=' | sort"
test_command "${HOME}"
test_command "cd"
test_command "cd \${HOME}"
test_command "echo \${HOME}"
test_command "pwd"
test_command "export A=5"
test_command "exit 0"
test_command "exit x"
test_command "exit 1"
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
test_command "echo $HOM\"E\""
test_command "echo \"$HOME\""

echo -ne "\n\n -> Testing memory leaks.\n\n "

test_leaks "echo ${HOME}"
test_leaks "export"
test_leaks "a=15 b=17"
test_leaks "cd ${HOME}"
test_leaks "env"
test_leaks "git status"
test_leaks "echo hola && echo adios"
test_leaks "git ls-files | grep \"\.c\""
test_leaks "(echo hola) && echo adios || echo que"
test_leaks "echo hola && (echo adios)"
test_leaks "echo hola adios | grep hola"
test_leaks "a=15 export | grep -v 'hola'"
test_leaks "( echo L1 && ( echo L2 && ( echo L3 && ( echo L4 ) ) ) )"
test_leaks "( echo X && ( echo Y && ( false && ( echo Z ) ) ) )"
test_leaks "echo hola > tmpfile && cat tmpfile && rm -f tmpfile"
test_leaks "echo hola > tmpfile && echo adios >> tmpfile && cat tmpfile && rm -f tmpfile"
test_leaks "echo 'hola' > tmpfile && cat < tmpfile && rm -f tmpfile"
test_leaks "( echo X && ( echo Y && ( false && ( echo Z | grep -v X | grep Z) ) ) )"

echo -ne "\n\n -> Not interactive usage.\n\n "

echo "cd srcs && cd .. && cd srcs && cd .. && cd s*" | ./minishell && echo -ne "$OK"
echo "./minishell -c 'echo \$MSHLVL'" | ./minishell > /dev/null && echo -ne "$OK"
PATH="$PATH:$PWD" test_leaks ./tests/run.sh
echo "echo hola || echo adios && echo que" | ./minishell > /dev/null && echo -ne "$OK"
echo "echo hola | grep hola || echo adios | grep adios && echo que | grep que" | ./minishell > /dev/null && echo -ne "$OK"

echo -ne "\n\n -> Test extended commands.\n\n "

test_command "(echo hola) && echo adios"
test_command "( echo L1 && ( echo L2 && ( echo L3 && ( echo L4 ) ) ) )"
test_command "echo hola && (echo adios)"
test_command "( echo A && ( false || ( echo B && ( echo C || echo D ) ) ) )"
test_command "echo hola && echo adios"
test_command "cd .. && echo hola && cd - && echo $PWD"
test_command "echo hola'adios'"
test_command "echo hola'$HOME'"
test_command "echo hola\"adios\""
test_command "echo hola\"$HOME\""
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
test_command "true && false && echo $?"
test_command "false || true && echo $?"
test_command "(false && true) || false && echo $?"
test_command "echo hola > /no/existe && echo nunca"
test_command "cat < /no/existe || echo fallback"
test_command "echo hola > dir_sin_permiso && rm dir_sin_permiso"
test_command "A=1 echo hola && echo $A"
test_command "cd / | pwd"
test_command "false && true || echo ok"
test_command "true || false && echo no"
test_command "echo hola > $HOME/tmpfile && cat $HOME/tmpfile && rm $HOME/tmpfile"
test_command "A=42 echo hola && env | grep '^A='"
test_command "A=42 echo hola && env | grep '^A='"
test_command "A=1 && export | grep ' A=' && echo $A"
test_command "echo hola | cat | cat | cat | grep h"

echo -e "\n"