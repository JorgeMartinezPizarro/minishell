#ifndef MINISHELL_JORGE_H

# define MINISHELL_JORGE_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"

// STRUCTURES
typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

// EXECUTION
int		is_built_in(char *str);
int		run_built_in(t_cmd *com);
int		run_program(t_cmd *com, t_shell *shell);
int		run_cd(t_cmd *com);
int 	run_echo(t_cmd *com);
int 	run_env(t_cmd *com, char *prefix);
int 	run_pwd(t_cmd *com);
int		run_export(t_cmd *com);
int		run_unset(t_cmd *com);
int		run_exit(t_cmd *com);

// EXPANSION
char	*expand_vars(char *s, t_list *env);
void	expand_wildcard_tokens(t_tokens **tokens, char *cwd);
void	expand_env_tokens(t_tokens **tokens, t_list *env);
char	**expand_wildcard(const char *cwd, const char *pattern);
t_list	*extract_variables(const char *str);

// UTILS
size_t	strarr_len(char **strs);
void	free_str_array(char **arr);
void	free_variable(void *content);
char	*get_prompt(t_list *env);
char	*join_paths(const char *base, const char *relative);

// ENVIRONMENTS
size_t	env_len_list(t_list *vars);
t_list	*ft_clone_env(t_list *env);
void	set_env_value(t_list **env, char *name, char *value);
void	del_env_value(t_list **env, char *value);
char	*get_env_value(t_list *env, char *name);
void	free_env(t_list **env);
t_list	*load_env_values(char **env);
char	**env_list_to_envp(t_list *env);

// SIGNALS
void	setup_signals_interactive(void);
void	setup_signals_child(void);
void	setup_signals_parent_waiting(void);

#endif