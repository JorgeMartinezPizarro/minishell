### ABSTRACT

MINISHELL – a simple, interactive shell.

   	* Total of lines: 2514
	* Total of files: 34

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

The MiniShell can be used as:

```sh
./minishell -c "command"
```

To run and check for memory leaks, use:

```sh
make run
```

You can also see the current MiniShells opened (with nested view) using:

```sh
make view
```

For it, open some nested MiniShells and run the command in another tab.

You can also use shebang as usual:

```sh
#!/path/to/minishell
echo hola
export A=15
echo $A
```

Running that script, the MiniShell will be used to process the commands.

It works only for the limited syntax of MiniShell.

The color of the prompt can be managed using the environment variable `COLOR`.

Allowed values: BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE.

### TODO:

* Copy to 42 only the Makefile, *.c, and *.h files:

  * Makefile (remove extra targets for the 42 copy)
  * includes
  * srcs
  * libft
