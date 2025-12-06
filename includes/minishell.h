#ifndef MINISHELL_H
# define MINISHELL_H

# define OR_S "||"
# define AND_S "&&"
# define PIPE_S "|"
# define APPEND_S ">>"
# define TRUNCATE_S ">"
# define REDIR_S "<"
# define HEREDOC_S "<<"

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	OR,
	AND,
	WORD,
	HEREDOC,
	TRUNCATE,
	PIPE = '|',
	REDIR = '<',
	APPEND = '>'
}	e_token_type;

typedef struct	s_token_list
{
	e_token_type	type;
	t_token_list	*next;
	char			*str;
}	t_token_list;

typedef struct	s_parsed_line
{
	char	**info;
}	t_parsed_line;

#endif