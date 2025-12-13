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
/*
en esta estructura estarán los tokens y las redirecciones de cada comando

en cada nodo copiar los tokens que debe contener

en el parseo hay que definir el outfile y el infile
*/


typedef struct	s_tree
{
	t_parse_list	*parse;
	struct s_tree	*right;
	struct s_tree	*left;
	bool			subproccess;
	bool			valid_line;
	bool			and;
	bool			or;
}	t_tree;
/*
En cada hoja del árbol quiero saber si es un proceso hijo y a partir de ahí crear el proceso hijo
si la línea es válida
*/

#endif