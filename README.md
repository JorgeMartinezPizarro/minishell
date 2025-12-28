### ABSTRACT

MINISHELL – a simple, interactive shell.

   	* Total of lines: 2132
	* Total of files: 34

### USAGE

To compile the project:

```sh
make
```

Run the program with:

```sh
./minishell
```

The MiniShell can be used as:

```sh
./minishell -c "command"
```

You can also use shebang as usual:

```sh
#!/path/to/minishell
echo hola
export A=15
echo $A
```

Running that script with ./script.sh, the MiniShell will be used to process the commands.

It works only for the limited syntax of MiniShell.

### TESTS

To run the tests:

```sh
make test
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

### COLORS

The color of the prompt can be managed using the environment variable `COLOR`.

Allowed values: BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE.
