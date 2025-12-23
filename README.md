### Minishell work for 42

Aqui podemos dejarnos comentarios o explicaciones de como van yendo las cosas.

### NOTES

En el repositorio de 42madrid debemos eliminar cualquier test, README.md o pdfs. Revisar bien antes de finalizar.

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

### T0D0:

- Trocear el codigo para mejor legibilidad. 

- Integrar bien los .h.

- Recordar para la entrega solo entregar Makefile, *.c y *.h
