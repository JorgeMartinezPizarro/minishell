#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>

typedef enum e_token_type
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
	T_REDIR_OUT = '>',
	T_SINGLE_QUOTE = '\'',
	T_DOUBLE_QUOTE = '\"'
}	e_token_type;

typedef enum e_node_type
{
	N_OR,
	N_AND,
	N_PIPE,
	N_CMND
}	e_node_type;

typedef struct	s_tokens
{
	struct s_tokens	*next;
	char			*str;
	int				type;
}	t_tokens;

typedef struct	s_cmd
{
	t_tokens	*tokens;
	char		*out_fd;
	char		*in_fd;
}	t_cmd;
//una vez separados los comandos ver si cada línea de ejecución es válida

typedef struct	s_range
{
	t_tokens	*start;
	t_tokens	*end;
}	t_range;

typedef struct	s_tree
{
	struct s_tree	*right;
	struct s_tree	*left;
	e_node_type		n_type;
	t_cmd			*cmd;
	bool			subshell;
}	t_tree;

t_tree	*make_tree(t_tokens *start, t_tokens *end);
int		tokenize(char *line, t_tokens **tokens);
void	free_tokens(t_tokens *tokens);

#endif