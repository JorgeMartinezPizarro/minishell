#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>

typedef enum e_token_type
{
	OR,
	AND,
	WORD,
	APPEND,
	HEREDOC,
	PIPE = '|',
	REDIR = '>',
	O_PAREN = '(',
	C_PAREN = ')',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"'
}	e_token_type;

typedef struct	s_token_list
{
	struct s_token_list	*next;
	char				*str;
	int					type;
}	t_token_list;

typedef struct	s_parse_list
{
	struct s_parse_list	*next;
	t_token_list		*tokens;
	bool				is_pipe;
	int					out_fd;
	int					in_fd;
}	t_parse_list;


typedef struct	s_parse
{
	t_parse_list	*parse_list;
	bool			subproccess;
	bool			valid_line;
	bool			and;
	bool			or;
}	t_parse;

typedef struct	s_tree
{
	t_parse			parse;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

t_tree	*make_tree(t_tree **tree, t_token_list *tokens);
int		tokenize(char *line, t_token_list **tokens);
void	free_tokens(t_token_list *tokens);

#endif