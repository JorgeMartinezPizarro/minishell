/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:43:46 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/25 19:58:06 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

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

#endif