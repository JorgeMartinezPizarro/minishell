## Main script for batch testing 

## Batch execution of several scenarios, 
## add more with the new code.

## Add new code, add here a working example

echo " -> Compiling minishell"
make jorge
echo " -> Running different tests"

./jorge -c "echo hola"

## Comando que falla, lo silenciamos
./jorge -c "echo"

./jorge -c "env"

## Comando que falla, lo silenciamos
./jorge -c "${HOME}" || true

./jorge -c "cd \$(HOME)"
./jorge -c "echo \${HOME}"
./jorge -c "pwd"
./jorge -c "export A=5"
./jorge -c "B=8"
./jorge -c "echo \${HOME}/dir"
./jorge -c "  \"hola\"  echo|hel*lo  "

echo " -> Cleanup"
make fclean > /dev/null
