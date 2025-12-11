#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	OR,
	AND,
	WORD,
	APPEND,
	HEREDOC,
	PIPE = '|',
	REDIR = '>',
	WILDCARD = '*',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	OPEN_PARENTHESIS = '(',
	CLOSE_PARENTHESIS = ')'
}	e_token_type;

typedef struct	s_token_list
{
	char				*str;
	int					type;
	struct s_token_list	*next;
}	t_token_list;

typedef struct	s_parsed_line
{
}	t_parsed_line;

#endif