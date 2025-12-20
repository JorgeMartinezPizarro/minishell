#ifndef MINISHELL_JORGE_H

# define MINISHELL_JORGE_H

// Debe estar lincada en el Makefile
# include "libft.h"

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
// Debe estar lincada en el Makefile
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"
# include "tokenizer.h"

// este tipo es para la t_list *env que gestiona las variables de entorno.
typedef struct s_variable
{
	char	*name;
	char	*value;
	bool	exported;
}	t_variable;

// Main command runner entrypoint.
int		is_built_in(t_cmd *com);
int		run_built_in(t_cmd *com);
int		run_program(t_cmd *com);

char	*expand_vars(char *s, t_list *env);

char	**expand_wildcard(const char *cwd, const char *pattern);

t_tokens	*expand_tokens(t_tokens *tokens, char *cwd);

// OBTIENE UNA LISTA CON LAS VARIABLES EN UN STRING
// UTIL PARA REEMPLAZARLAS DESPUES POR SU VALOR

t_list	*extract_variables(const char *str);

// UNE CAMINO ABSOLUTO + RELATIVO 
char	*join_paths(const char *base, const char *relative);
// tamaño del char ** 
size_t	strarr_len(char **strs);

void	free_str_array(char **arr);

size_t	env_len_list(t_list *vars);

t_list	*ft_clone_env(t_list *env);

void	set_env_value(t_list **env, char *name, char *value);

void	del_env_value(t_list **env, char *value);

char	*get_env_value(t_list *env, char *name);

void	free_env(t_list **env);

t_list	*load_env_values(char **env);

int run_cd(t_cmd *com);
int run_echo(t_cmd *com);
int run_env(t_cmd *com);
int run_pwd(t_cmd *com);
int	run_export(t_cmd *com);
int	run_set(t_cmd *com);
int	run_unset(t_cmd *com);

#endif