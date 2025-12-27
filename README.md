### ABSTRACT

MINISHELL – a simple, interactive shell.

  - Total of lines: 2514
  - Total of files: 34

### USAGE

To compile the project:

```sh
make 
```

To run the tests:

```sh
make test
```

Run the program with:


```sh
./minishell
```

### ADVANCED

The minishell can be used as:

```sh
./minishell -c "command"
```

To run and check for memory leaks use:

```sh
make run
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

Running that script, the minishell will be used to process the commands.

It work only for the limited syntaxis of minishell.

The color of the prompt can be managed using the env `COLOR`.

Allowed values: BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE.

### TODO:

- Copiara a 42 solo Makefile, *.c y *.h.

	- Makefile (eliminar los targets extras en la copia de 42)
	- includes
	- srcs
	- libft
