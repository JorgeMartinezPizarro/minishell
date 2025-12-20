#ifndef MINISHELL_JORGE_H

# define MINISHELL_JORGE_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"

// estructura para las variables de entorno de cmd->env
typedef struct s_variable
{
	char	*name;
	char	*value;
	bool	exported;
}	t_variable;

// Main Execution
int		is_built_in(t_cmd *com);
int		run_built_in(t_cmd *com);
int		run_program(t_cmd *com);
// Execution functions
int		run_cd(t_cmd *com);
int 	run_echo(t_cmd *com);
int 	run_env(t_cmd *com);
int 	run_pwd(t_cmd *com);
int		run_export(t_cmd *com);
int		run_set(t_cmd *com);
int		run_unset(t_cmd *com);

// Main expansion
char	*expand_vars(char *s, t_list *env);
t_tokens	*expand_tokens(t_tokens *tokens, char *cwd);

// Expansion functions
char	**expand_wildcard(const char *cwd, const char *pattern);
t_list	*extract_variables(const char *str);

// char ** utils
size_t	strarr_len(char **strs);
void	free_str_array(char **arr);

// For CWD management and command in PATH search.
char	*join_paths(const char *base, const char *relative);

// Environment management
size_t	env_len_list(t_list *vars);
t_list	*ft_clone_env(t_list *env);
void	set_env_value(t_list **env, char *name, char *value);
void	del_env_value(t_list **env, char *value);
char	*get_env_value(t_list *env, char *name);
void	free_env(t_list **env);
t_list	*load_env_values(char **env);
char **env_list_to_envp(t_list *env);

#endif