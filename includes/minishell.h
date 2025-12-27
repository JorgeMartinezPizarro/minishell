/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 21:44:45 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/27 14:47:18 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <stdlib.h>

# define MAX_MINISHELL_LEVEL 1000

///////////////////////////////////////////////////////////////////////////////
//
//  NOTES:
//
//  The MiniShell comes with the following features:
//
//  1 - MiniShell accepts single-line commands; pasting multiline commands
//      will execute only the first line.
//  2 - MiniShell can be used as a shebang, with a very limited syntax.
//  3 - MiniShell accepts non-interactive execution, can run scripts, and can
//      also be used as ./minishell -c "command".
//  4 - MiniShell implements env, export, cd, unset, exit, and pwd. For other
//      commands it searches in PATH for executables, as Bash does.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GLOBALS
///////////////////////////////////////////////////////////////////////////////
extern int	g_exit_code;

///////////////////////////////////////////////////////////////////////////////
// STRUCTURES
///////////////////////////////////////////////////////////////////////////////
typedef struct s_variable
{
	char	*name;
	char	*value;
	int		exported;
}	t_variable;

typedef enum e_exit_code
{
	EXIT_OK = 0,
	EXIT_GENERAL_ERROR = 1,
	EXIT_CANT_EXEC = 126,
	EXIT_NOT_FOUND = 127,
	EXIT_SIGINT = 130
}	t_exit_code;

typedef enum t_token_type
{
	T_OR,
	T_AND,
	T_WORD,
	T_APPEND,
	T_HEREDOC,
	T_PIPE = '|',
	T_O_PAREN = '(',
	T_C_PAREN = ')',
	T_REDIR_IN = '<',
	T_REDIR_TR = '>'
}	t_token_type;

typedef enum t_node_type
{
	N_OR,
	N_AND,
	N_PIPE,
	N_CMND
}	t_node_type;

typedef struct s_tokens
{
	struct s_tokens	*next;
	char			*str;
	int				type;
}	t_tokens;

typedef struct s_redir
{
	t_token_type	redir_type;
	t_tokens		*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_list		*env;
	t_tokens	*args;
	t_redir		*redirs;
	bool		is_builtin;
}	t_cmd;

typedef struct s_tree
{
	struct s_tree	*right;
	struct s_tree	*left;
	t_node_type		n_type;
	t_cmd			*cmd;
	bool			subshell;
}	t_tree;

typedef struct s_shell
{
	t_tree	*first_node;
	t_list	*env;
	bool	is_child;
}	t_shell;

typedef struct s_expand_ctx
{
	const char	*fs_base;
	const char	*rel_base;
	char		**segments;
	int			idx;
	char		***out;
}	t_expand_ctx;

///////////////////////////////////////////////////////////////////////////////
// EXECUTION
///////////////////////////////////////////////////////////////////////////////
int			is_built_in(char *str);
int			run_built_in(t_cmd *com, t_shell *shell);
int			run_program(t_cmd *com, t_shell *shell);
int			run_cd(t_cmd *com);
int			run_echo(t_cmd *com);
int			run_env(t_cmd *com);
int			run_pwd(t_cmd *com);
int			run_export(t_cmd *com);
int			run_unset(t_cmd *com);
int			run_exit(t_shell *shell);
int			run_assign(t_cmd *com, t_shell *shell);
char		*find_executable(const char *cmd, t_list *env);
int			is_valid_identifier(const char *name);
int			make_redirections(t_redir *redirs, t_list *env);
void		exec_tree(t_tree *tree, t_shell *shell);
void		exec_pipe(t_tree *tree, t_shell **shell);
void		free_shell(t_shell *shell);
void		free_tree(t_tree *tree);

///////////////////////////////////////////////////////////////////////////////
// EXPANSION
///////////////////////////////////////////////////////////////////////////////
char		*expand_vars(char *s, t_list *env);
void		expand_wildcard_tokens(t_tokens **tokens, char *cwd);
void		expand_env_tokens(t_tokens **tokens, t_list *env);
char		**expand_wildcard(const char *cwd, const char *pattern);
t_list		*extract_variables(const char *str);
void		restore_dollars(char *s, char mark);
void		mark_dollars(char *s, char mark);
char		*trim_quotes(char *s);
void		expand_recursive_rel(t_expand_ctx *ctx);

///////////////////////////////////////////////////////////////////////////////
// UTILS
///////////////////////////////////////////////////////////////////////////////
size_t		strarr_len(char **strs);
void		free_str_array(char **arr);
void		free_variable(void *content);
char		*get_prompt(t_list *env);
char		*join_paths(const char *base, const char *relative);
void		print_error(const char *str1, const char *str2);
void		malloc_failed(void);
char		**str_array_add(char **arr, char *s);
int			is_directory(const char *path);

///////////////////////////////////////////////////////////////////////////////
// ENVIRONMENTS
///////////////////////////////////////////////////////////////////////////////
size_t		env_len_list(t_list *vars);
t_list		*clone_env(t_list *env);
void		set_env_value(t_list **env, char *name, char *value, int exported);
void		del_env_value(t_list **env, char *value);
char		*get_env_value(t_list *env, char *name);
void		free_env(t_list **env);
t_list		*load_env_values(char **env);
char		**env_list_to_envp(t_list *env);
void		print_sorted_env(t_list *env);
void		update_minishell_level(t_list **env);
void		init_required_env(t_list **env);

///////////////////////////////////////////////////////////////////////////////
// SIGNALS
///////////////////////////////////////////////////////////////////////////////
void		setup_signals_interactive(void);
void		setup_signals_child(void);
void		setup_signals_parent_waiting(void);

///////////////////////////////////////////////////////////////////////////////
// PARSER
///////////////////////////////////////////////////////////////////////////////
t_tokens	*division_point(t_tokens *start, t_tokens *end);
t_tree		*make_tree(t_tokens *start, t_tokens *end);
void		syntax_error(void);
void		free_cmnd(t_cmd *cmd);
bool		is_redir(t_tokens *token);
void		iter_paren(t_tokens **tokens);
void		add_redir(t_redir **redirs, t_tokens *token);
void		assign_node_type(t_tree **node, t_tokens *token);
bool		everything_inside_paren(t_tokens *start, t_tokens *end);
t_tokens	*remove_paren(t_tree **tree, t_tokens **start, t_tokens *end);

///////////////////////////////////////////////////////////////////////////////
// TOKENIZER
///////////////////////////////////////////////////////////////////////////////
void		add_token_to_list(t_tokens **tokens, char *str, int type);
int			tokenize(char *line, t_tokens **tokens);
void		print_tokens(t_tokens *tokens);
void		free_tokens(t_tokens *tokens);
int			which_operator(char *line);
bool		valid_quotes(char *line);
bool		valid_paren(char *line);
char		*iter_line(char *line);

#endif