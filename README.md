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

El comando lleva un puntero al entorno, y en exec_tree se pasa de comando a comando. t_cmd contiene por diseño cwd con el path actual
y env con la t_list de t_variables. En run_program necesitas tener los env actuales, y aunque no haga falta ahi cwd, es util para la parte
de los built ins.

### TODO JORGE:

- Negociar con mangit la gestion del exit, run_built_in devuelve un codigo pero no puede directamente matar la minishell directamente (por los frees). 
- Trocear el codigo para mejor legibilidad. 
- Creo que un header con 25 funciones es suficientemente legible, pero podemos partir mis funciones de forma tematica (hablar con mangit).
- Ctrl C + Ctrl D NECESITA una variable global para ver que proceso debe reaccionar a la signal.
- Revisar el problema actual al cargar ./minishell de forma recursiva muchas veces.