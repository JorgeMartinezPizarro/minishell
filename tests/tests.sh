## Main script for batch testing 

## Batch execution of several scenarios, 
## add more with the new code.

## Add new code, add here a working example

echo " -> Compiling minishell"
make 
echo " -> Running different tests"

./minishell -c "echo hola"

## Comando que falla, lo silenciamos
./minishell -c "echo"

./minishell -c "env"

## Comando que falla, lo silenciamos
./minishell -c "${HOME}" || true

./minishell -c "cd \$(HOME)"
./minishell -c "echo \${HOME}"
./minishell -c "pwd"
./minishell -c "export A=5"
./minishell -c "B=8"
./minishell -c "echo \${HOME}/dir"
./minishell -c "  \"hola\"  echo|hel*lo  " || true

echo " -> Cleanup"
make fclean > /dev/null
