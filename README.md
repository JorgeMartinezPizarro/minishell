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
int run_command(t_command *com)
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
}	t_command;
```

La lista t_list (\*env) castea content de (void\*) a (t_variable\*).

Debemos encontrar un punto comun entre `t_command` y tu `t_parsed_line`. 

He dejado terminado como prototipo unset, export y A=b, aun no hay control de errores ni parseo de argumentos, eso deberiamos hacerlo en una fase previa, el tokenizer, que genere la estructura t_command lista para usar. En la misma definicion de t_command se puede eliminar el \n final y los caracteres que sea necesario, los "" de un string por ejemplo, no se imprimen en echo.
