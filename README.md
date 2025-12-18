### Minishell work for 42

Aqui podemos dejarnos  comentarios o explicaciones de como van yendo las cosas.

### NOTES

En el repositorio de 42madrid debemos eliminar cualquier test, README.md o pdfs. Revisar bien antes de finalizar.

### Commandos

Usa

```sh
make run
```

to compile and run the latest version of minitalk.


Con

```sh
make jorge "comando"
```

se ejecutara el comando "comando"

Con 

```sh
make jorge
```

se abre la shell version de jorge, no acepta tokens especiales, solo uso de variables, cd, env, echo y pwd de momento.

### NOTAS SOBRE MI CODIGO:

He creado una estructura con char *command, char **args, int argc, t_list *env (lista enlazada de variables) basicamente. Ademas mantengo cdw en la estructura, lo cargo en el primer run usando la funcion de C para ello, getcwd.

He construido los basicos para manipular variables, set get delete y free:


```c
void	set_env_value(t_list **env, char *name, char *value);
void	del_env_value(t_list **env, char *value);
char	*get_env_value(t_list *env, char *name);
void	free_env(t_list **env);
```

Para el comando `cd` he creado una utilidad:

```c
char	*join_paths(const char *base, const char *relative);
```

que aplica un path relativo sobre otro absoluto para obtener uno absoluto. Esto se usa en `cd`. Notese que cd modifica la environment var PWD en shell, manteniendo esta variable siempre la posicion actual. Ojo que hay tambien OLDPWD para cd ~ por ejemplo. Creo que eso no lo necesitamos implementar.

Para `echo` y para otros comandos en general, he creado usando las environment variables un:

```c
char	*expand_vars(char *s, t_list *env);
```

Este comando reemplaza cada `$1` o `${var}` por su valor respectivo en el string.

Por ultimo, dado char *command y char **args, he creado una funcion:

```c
int run_built_in(t_cmd *com)
```

Que centraliza y separa por casos, falta aun la asignacion de variables, `A=15` es un comando valido que define un env, igual que `export A=15`.

Mi estructura de momento es

```c
typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

typedef struct s_command
{
	char		*command;
	char		*cwd;
	char		**args;
	size_t		argc;
	t_list		*env;
}	t_cmd;
```

La lista t_list (\*env) castea content de (void\*) a (t_variable\*).

Debemos encontrar un punto comun entre `t_cmd` y tu `t_parsed_line`. 

He dejado terminado como prototipo unset, export y A=b, aun no hay control de errores ni parseo de argumentos, eso deberiamos hacerlo en una fase previa, el tokenizer, que genere la estructura t_cmd lista para usar. En la misma definicion de t_cmd se puede eliminar el \n final y los caracteres que sea necesario, los "" de un string por ejemplo, no se imprimen en echo.

Lo suyo es que la estructura t_cmd contenga los tokens, las env, el comando, y toda la informacion estructurada. Yo puse char *command y char **args para los demas, pero ahi es donde lo podemos cambiar por t_parsed_line.

Fijate bien si podemos juntar ambos codigos usando esta estrategia.

En el arbol binario de comandos, al traversar el arbol (ejecutar el comando compuesto), en cada paso cambiamos el comando y los args pero mantenemos las variables de entorno, el cwd, no haria falta hacer clone, solo pasamos la estructura y cada iteracion en el arbol de comandos, ejecutamos un t_cmd que va cambiando.

