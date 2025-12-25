### Minishell work for 42

Aqui podemos dejarnos comentarios o explicaciones de como van yendo las cosas.

### NOTES

En el repositorio de 42madrid debemos eliminar cualquier test, README.md o pdfs. Revisar bien antes de finalizar.

### FORK BOMB

Para destruir un sistema, el fork bomb clasico, que define funciones vacias y las lanza de forma recursiva en background, es el siguiente:

```sh
:(){ :|:& };:
```

## COLORES:

Se puede configurar el color del prompt usando la variable de entorno `COLOR`:

Allowed values: BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE.

## GIT:

Para trabajar en el mismo branch, hay dos vias:

- Hacer commit del trabajo local:

```sh
	git commit -a -m "local changes"
	git pull --rebase
	## Aqui solucionamos los conflictos si los hay
	git rebase --continue ## Si habia conflictos
	git push
```

- Sin hacer commit del trabajo local:

```sh
	git stash
	git pull
	git stash pop
	## Aqui solucionamos los conflictos si los hay
```

### Commandos

Use

```sh
make 
```

to compile the latest version of minishell. 

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

You can also use shebang as usual:

```sh
#!/path/to/minishell 
echo hola
```

Al ejecutar ./script.sh, se ejecutara usando minishell.

### TODO:

- Implementar asignacion de variables sin export (run_assign)

- Revisar la norma.

- Integrar bien los .h.

- Recordar para la entrega solo entregar Makefile, *.c y *.h

- Revisar leaks con valgrind.

- bug tokenizer: `echo hola"adios"` falla contra shell.

- usar \x01 para marcar los $ que deben expandirse.

- tokens no saben de sus quotes, esas se usan para decidir si un $ se vuelve \x01$ para que sea reemplazado, o no.

- casos rotos:

	- echo "hola"adios
	- cd "sr"cs

- Repasar nuestra decision al ejecutar ficheros:

`README.md`

Es distinta, bash si no encuentra shebang pero es texto, intenta ejecutarlo usando bash por defecto, y en este caso muestra un error por linea,
nosotros, sin embargo

```bash
jorge@DESKTOP-LGCI8TT >>> README.md
execve: Exec format error
```

- bash run.sh ejecuta el archivo run.sh, podemos imitarlo, no es demasiado muy complicado.

- Ficheros con problemas de norma:

main.c: Error!
run_assign.c: Error!
run_built_in.c: Error!
run_export.c: Error!
environments3.c: Error!
run_program.c: Error!
expand_env_tokens.c: Error!
expand_wildcard.c: Error!
parser_utils.c: Error!
tokenizer.c: Error!
token_utils.c: Error!