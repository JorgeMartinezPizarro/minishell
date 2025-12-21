### Minishell work for 42

Aqui podemos dejarnos  comentarios o explicaciones de como van yendo las cosas.

### NOTES

En el repositorio de 42madrid debemos eliminar cualquier test, README.md o pdfs. Revisar bien antes de finalizar.

### Commandos

Use

```sh
make 
```

to compile the working code, in `main_tmp.c`. 


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

### NOTA IMPORTANTE:

expand_vars funciona con el patron

str = expand_vars(str)

es menos compacto que expand_vars(&str) pero se lee mejor.

El patron arriba indicado, significa que el contenido de str se libera dentro de la funcion.

### TODOS:

- Gestion de exit
- Trocear el codigo para mejor legibilidad. 
- Integrar bien los .h.
- Reparar expand_tokens (integracion con expand_wildcards).
- Arreglar exec_tree:
	- (echo hola) && (echo adios) da problemas.
	- export a=5 && echo $a no imprime nada.
