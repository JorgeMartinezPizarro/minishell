### Minishell work for 42

The MINIshell

### COLORES:

Se puede configurar el color del prompt usando la variable de entorno `COLOR`:

Allowed values: BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE.

### Commandos

Use

```sh
make 
```

to compile the latest version of minishell. 

To see the total progress of the repo:

```sh
make stats
```

The command


```sh
./minishell
```

opens the minishell interactively. Using

```sh
./minishell -c "command"
```

it runs a single command.

Alternatively, you can use:

```sh
make run
```

to run the minishell with `valgrind`.

Finally, to run the tests, you can run

```sh
make test
```

You can also see the current minishells openend (with nested view) using:

```sh
make view
```

For it, open some nested minishells and run the command in another tab.

You can also use shebang as usual:

```sh
#!/path/to/minishell 
echo hola
export A=15
echo $A
```

Al ejecutar ./script.sh, se ejecutara usando minishell.

Esta opcion del shebang es limitada, el parser intenta ejecutar cada linea no vacia asi pues no es exactamente igual que bash pero permite ejecutar scripts!

### TODO:

- Copiara a 42 solo Makefile, *.c y *.h.

	- Makefile (eliminar los targets extras en la copia de 42)
	- includes
	- srcs
	- libft
