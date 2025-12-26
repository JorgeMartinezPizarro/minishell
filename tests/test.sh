#!/bin/bash

OK="\033[1;32mOK\033[0m "
KO="\033[1;31mKO\033[0m "

### Use bash to validate exit codes
### of commands and diff for results

echo -ne " -> Running norminette\n\n "

validate_norm(){
    
    # Ejecutar norminette, capturar stdout y stderr
    norm_out=$(norminette "$1" | grep -v locale || true)
	files=$(find $1 -type f | wc -l)
    # Contar cuántas veces aparece "Error:"
    error_count=$(echo "$norm_out" | grep -c "Error:" || true)

    if [ "$error_count" -ne 0 ]; then
		norminette -R CheckForbiddenHeaders -R CheckDefine "$1" | head -n40
        echo -ne "$KO"
        return 1
    else
        echo -ne "$OK"
        return 0
    fi
}

validate_norm ./srcs
validate_norm ./includes
validate_norm ./libft

echo -ne "\n\n -> Running different tests\n\n "

./minishell -c "echo hola" > /dev/null && echo -ne "$OK"

./minishell -c "echo" > /dev/null && echo -ne "$OK"

./minishell -c "export" > /dev/null && echo -ne "$OK"

## Comando que falla, lo silenciamos
./minishell -c "${HOME}"  > /dev/null 2>&1 || echo -ne "$OK"

./minishell -c "cd" > /dev/null && echo -ne "$OK"
./minishell -c "cd \${HOME}" > /dev/null && echo -ne "$OK"
./minishell -c "echo \${HOME}" > /dev/null && echo -ne "$OK"
./minishell -c "pwd" > /dev/null && echo -ne "$OK"
./minishell -c "export A=5" > /dev/null && echo -ne "$OK"
./minishell -c "export B=8" > /dev/null && echo -ne "$OK"
./minishell -c "echo \${HOME}/dir" > /dev/null && echo -ne "$OK"
## Comando que falla, lo silenciamos
./minishell -c "  \"hola\"  echo|hel*lo  "  > /dev/null 2>&1 || echo -ne "$OK"

echo -ne "\n\n -> Testing memory leaks\n\n "
## Probamos que no haya leaks en varios comandos 
valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "echo ${HOME}" > /dev/null && echo -ne "$OK"

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "export" > /dev/null && echo -ne "$OK"

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "a=15 b=17" > /dev/null && echo -ne "$OK"

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "cd ${HOME}" > /dev/null && echo -ne "$OK"

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "env" > /dev/null && echo -ne "$OK"

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c "git status" > /dev/null && echo -ne "$OK"

## Exportamos path para ejecutar run.sh, ese fichero busca
## minishell para ejecutarse (shebang). Esto valida que nuestra
## minishell es usable para ejecutar ficheros.
export PATH="$PATH:$PWD"

valgrind \
		--leak-check=full --show-leak-kinds=all --gen-suppressions=all \
		--suppressions=readline.supp --errors-for-leak-kinds=all \
		--quiet \
		./minishell -c ./tests/run.sh > /dev/null && echo -ne "$OK"

./minishell -c "echo hola && echo adios" > /dev/null && echo -ne "$OK"

./minishell -c "(echo hola) && echo adios" > /dev/null && echo -ne "$OK"

./minishell -c "(cd r || echo fail 1 && cd x) || echo fail 2" > /dev/null 2>&1 && echo -ne "$OK"

echo -ne "\n\n -> Some additional tests\n\n "

## Prueba de que las wildcards se expanden apropiadamente.
echo "cd srcs && cd .. && cd srcs && cd .. && cd s*" | ./minishell && echo -ne "$OK"

## Probamos que MSHLVL sube a 2.
echo "./minishell -c 'echo \$MSHLVL'" | ./minishell > /dev/null && echo -ne "$OK"

## Probamos que el entorno padre no se altera por el
## entorno hijo:

# Output esperado
expected="2
1"

# Ejecutamos el comando y capturamos la salida
output=$(export A=1 && A=2 ./minishell -c "echo \$A" && echo $A)

# Comparamos con diff
if diff <(echo "$expected") <(echo "$output") >/dev/null; then
    # Verde para OK
    echo -ne "$OK"
else
    # Rojo para KO y mostramos diff
    echo -ne "$KO"
    echo "Expected:"
    echo "$expected"
    echo "Got:"
    echo "$output"
fi

## Validamos expansiones complejas!

OUTPUT1=$(echo "hola'$USER'"adios)

OUTPUT2=$(./minishell -c "echo \"hola'$USER'\"adios")

if [[ "$OUTPUT1" == "$OUTPUT2" ]]; then
    echo -ne "$OK"
else
    echo -ne "$KO"
fi

## Helper para comparar output de minishell contra 
## output de bash. Ojo que los mensajes de error pueden
## diferir.
test_command() {
	# Usamos timeout para que no se quede bloqueado
	HEREDOC_CMD="$1"
	OUTPUT=$(timeout 1s ./minishell -c "$HEREDOC_CMD" 2>/dev/null) 
	EXIT_CODE=$?

	# Bash reference output
	EXPECTED=$(bash -c "$HEREDOC_CMD")

	# Evaluamos
	if [[ $EXIT_CODE -ne 0 ]]; then
		# Se bloquea o falla como se espera
		echo -ne "$KO"
		echo -e "\n\n Command: \n $HEREDOC_CMD "
		echo -e "\n\n The command did not finish properly."
		echo -e "\n Expected:\n $EXPECTED\n Got:\n $OUTPUT"
	else
		# Compara con bash para ver si accidentalmente funciona
		if [[ "$OUTPUT" == "$EXPECTED" ]]; then
			echo -ne "$OK"
		else
			echo -ne "$KO"
			echo -e "\n Expected:\n $EXPECTED\n Got:\n $OUTPUT"
		fi
	fi
}

test_command "echo hola && echo adios"

test_command "cd .. && echo hola && cd -"

test_command "echo hola'adios'"

test_command "echo $PWD && cd .. && cd - && echo $PWD"

test_command "A=150 export | grep -v 'MSHLVL' | grep -v ' _='"

test_command "A=150 env | grep -v 'MSHLVL' | grep -v '^_=' | sort"

## Test heredoc
echo -ne "\n\n -> Testing heredoc\n\n "

# Testeamos heredoc con variable
test_command 'NOMBRE="George" && cat <<EOF
Hola $NOMBRE
EOF'

echo -e "\n"