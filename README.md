### Minishell work for 42

Aqui podemos dejarnos comentarios o explicaciones de como van yendo las cosas.

### NOTES

En el repositorio de 42madrid debemos eliminar cualquier test, README.md o pdfs. Revisar bien antes de finalizar.

El heredoc solo funciona interactivamente, no pegandole varias lineas de golpe como en bash.

El interprete de minishell acepta varias lineas seguidas pegadas en la terminal.

Minishell permite ser usado como shebang. El parser es trivial, solo permite comandos validos en minishell y lineas vacias.

### FORK BOMB

Para destruir un sistema, el fork bomb clasico, que define funciones vacias y las lanza de forma recursiva en background, es el siguiente:

```sh
:(){ :|:& };:
```

Pero no nos es util, esto solo sirve para destruir sistemas en general. 

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

- Reorganizar los *.h

- Recordar para la entrega solo entregar Makefile, *.c y *.h

- Comentarios solo en el .h y solo en ingles.

- Revisar file descriptors abiertos con pipes o heredocs

- Revisar memory leaks de las pipes. Ahi hay muchos exit que no hacen free total.

- El heredoc con multi line paste no funciona por diseno, no es problema con el enunciado pero hay que tenerlo claro.

