/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_jorge.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 21:44:45 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 18:11:17 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_JORGE_H

# define MINISHELL_JORGE_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"

# define MAX_MINISHELL_LEVEL 1000

// STRUCTURES
typedef struct s_variable
{
	char	*name;
	char	*value;
	int		exported;
}	t_variable;

// EXECUTION
int		is_built_in(char *str);
int		run_built_in(t_cmd *com, t_shell *shell);
int		run_program(t_cmd *com, t_shell *shell);
int		run_cd(t_cmd *com);
int		run_echo(t_cmd *com);
int		run_env(t_cmd *com);
int		run_pwd(t_cmd *com);
int		run_export(t_cmd *com);
int		run_unset(t_cmd *com);
int		run_exit(t_shell *shell);
int		run_assign(t_cmd *com, t_shell *shell);
char	*find_executable(const char *cmd, t_list *env);
int		is_valid_identifier(const char *name);
int		exec_line(t_shell *shell, char *line);

// EXPANSION
char	*expand_vars(char *s, t_list *env);
void	expand_wildcard_tokens(t_tokens **tokens, char *cwd);
void	expand_env_tokens(t_tokens **tokens, t_list *env);
char	**expand_wildcard(const char *cwd, const char *pattern);
t_list	*extract_variables(const char *str);
void	restore_dollars(char *s, char mark);
void	mark_dollars(char *s, char mark);
char	*trim_quotes(char *s);
void	expand_recursive_rel(t_expand_ctx *ctx);

// UTILS
size_t	strarr_len(char **strs);
void	free_str_array(char **arr);
void	free_variable(void *content);
char	*get_prompt(t_list *env);
char	*join_paths(const char *base, const char *relative);
void	print_error(const char *str1, const char *str2);
void	malloc_failed(void);
char	**str_array_add(char **arr, char *s);
int		is_directory(const char *path);

// ENVIRONMENTS
size_t	env_len_list(t_list *vars);
t_list	*clone_env(t_list *env);
void	set_env_value(t_list **env, char *name, char *value, int exported);
void	del_env_value(t_list **env, char *value);
char	*get_env_value(t_list *env, char *name);
void	free_env(t_list **env);
t_list	*load_env_values(char **env);
char	**env_list_to_envp(t_list *env);
void	print_sorted_env(t_list *env);
void	update_minishell_level(t_list **env);
void	init_required_env(t_list **env);

// SIGNALS
void	setup_signals_interactive(void);
void	setup_signals_child(void);
void	setup_signals_parent_waiting(void);

#endif