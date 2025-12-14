#ifndef MINISHELL_JORGE_H

# define MINISHELL_JORGE_H

// Debe estar lincada en el Makefile
# include "libft.h"

# include <unistd.h>

// Debe estar lincada en el Makefile
# include <readline/readline.h>
# include <readline/history.h>

// El parseador del main debe primero identificar si hay redirect a fichero, en caso de echo
// y debera construir con el string que le de el usuario, un arbol de t_commands,
// es decir, una estructura como t_list pero con command_left y command_right, que se ejecutaran
// si el comando padre da 0 o 1.

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
	int			exit_code;
}	t_command;

// construimos los comandos con el parser y el tokenizer.
// despues, run_command recibe segun sea necesario cada t_command por separado, uno tras otro.

typedef struct s_tree
{
	t_command *command;
	struct s_tree *left_command;
	struct s_tree *right_command;
} t_tree;

// Main command runner entrypoint.
int		run_command(t_command *com);

char	*expand_vars(char *s, t_list *env);

// OBTIENE UNA LISTA CON LAS VARIABLES EN UN STRING
// UTIL PARA REEMPLAZARLAS DESPUES POR SU VALOR

t_list	*extract_variables(const char *str);

// UNE CAMINO ABSOLUTO + RELATIVO 
char	*join_paths(const char *base, const char *relative);

// tamaño del char ** 
size_t	strarr_len(char **strs);

// MANEJO DE ENTORNO

// tamaño de la lista enlazada
size_t	env_len_list(t_list *vars);
// clonar lista
t_list	*ft_clone_env(t_list *env);
// set value, replace or add new env
void	set_env_value(t_list **env, char *name, char *value);
// remove a env value if it exists
void	del_env_value(t_list **env, char *value);
// devuelve el valor de una var env
char	*get_env_value(t_list *env, char *name);
// libera la lista enlazada
void	free_env(t_list **env);
// carga la lista enlazada desde char ** de forma INICIAL
t_list	*load_env_values(char **env);

#endif