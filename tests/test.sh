## Main script for batch testing 

## Batch execution of several scenarios, 
## add more with the new code.

## Add new code, add here a working example

echo " -> Compiling minishell"
make jorge > /dev/null
echo " -> Running different tests"

./jorge "echo hola"

## Comando que falla, lo silenciamos
./jorge "echo" || true

./jorge "env"

## Comando que falla, lo silenciamos
./jorge "${HOME}" || true

./jorge "cd \$(HOME)"
./jorge "echo \${HOME}"
./jorge "pwd"

echo " -> Cleanup"
make fclean > /dev/null
