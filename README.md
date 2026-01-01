ABSTRACT
--------

MiniShell is a simple interactive shell implementing a coherent and well-defined
subset of POSIX-like shell semantics.

- Total of lines: 2222
- Total of files: 35

The project focuses on correct execution semantics rather than full bash
compatibility. Operator precedence, command grouping, pipelines, redirections
and exit status propagation are handled consistently and validated against
`bash -c`.

SUPPORTED FEATURES
------------------

Built-in commands:
- cd
- echo (with -n)
- pwd
- export (including assignments like a=1)
- env
- exit (with optional numeric argument)

Operators and grouping:
- Command grouping with parentheses: ( )
- Logical operators: &&, ||
- Pipelines: |
- Redirections: <, >, >>, <<

Execution model:
- Proper operator precedence between |, && and ||
- Correct exit status propagation across pipelines and grouped commands
- Environment scoping for temporary assignments (e.g. A=42 command)
- PATH-based command resolution for external programs

Usage modes:
- Interactive shell
- Non-interactive execution using -c
- Limited shebang support

LIMITATIONS
-----------

This project does not aim to fully replicate bash or POSIX shells.

Known limitations include:
- No job control
- No background execution
- No advanced globbing or expansion
- No multiline command parsing (only the first line is executed)
- Partial POSIX compliance by design

USAGE
-----

Compile the project:

```sh
make
```

Run the shell interactively:

```sh
./minishell
```

Run a single command:

```sh
./minishell -c "command"
```

SHEBANG USAGE
-------------

MiniShell can be used as an interpreter via shebang:

```sh
#!/path/to/minishell
echo hola
export A=15
echo $A
```

Running the script with:

```sh
./script.sh
```

will execute it using MiniShell. Only the supported MiniShell syntax is guaranteed
to work.

TESTS
-----

To run the full test suite:

```sh
make test
```

The test suite acts as an executable specification of the supported shell
semantics and compares MiniShell behavior against `bash`.

To run with memory leak checks:

```sh
make run
```

To visualize currently running MiniShell instances (nested view):

```sh
make view
```

For this, open several nested MiniShells and run the command in another terminal.

COLORS
------

The prompt color can be configured using the `COLOR` environment variable.

Allowed values:
BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE.

TODO
----

Fix redirect from outside subshell, (echo hola) > temp.

Fix ~ usage. Expansion before *, error if no HOME defined.