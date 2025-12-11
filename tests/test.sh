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
## Comando que falla, lo silenciamos
./jorge "cd \$(HOME)" || true
./jorge "echo \$(HOME)"
./jorge "echo \${HOME}"

echo " -> Cleanup"
make fclean > /dev/null
