#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_tokens_line
{
	t_token			*token;
	e_token_type	type;
}	t_tokens_line;

typedef enum e_token_type
{
	WORDS,
	REDIR_APPEND,
	REDIR_TRUNCATE,
	REDIR_OPEN,
	HEREDOC_OPEN
}	e_token_type;

typedef struct	s_token
{
	e_token_type type;
}	t_token;

typedef struct	s_parsed_line
{
	char	**info;
}	t_parsed_line;

#endif