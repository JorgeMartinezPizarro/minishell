/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:35:11 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/24 01:15:55 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		free_tokens(tmp->file);
		free(tmp);
	}
}

bool	is_string(t_tokens *token)
{
	if (token->type == T_WORD || token->type == T_SINGLE_QUOTE
		|| token->type == T_DOUBLE_QUOTE)
		return (true);
	return (false);
}

bool	is_redir(t_tokens *token)
{
	if (token->type == T_APPEND || token->type == T_HEREDOC
		|| token->type == T_REDIR_IN || token->type == T_REDIR_TR)
		return (true);
	return (false);
}

void	add_redir(t_redir **redirs, t_tokens *token)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = ft_calloc(sizeof(t_redir), 1);
	if (!new_redir)
		free_redirs(*redirs);
	new_redir->redir_type = token->type;
	token = token->next;
	add_token_to_list(&new_redir->file, token->str, token->type);
	new_redir->next = NULL;
	if (!redirs || !*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

void	iter_paren(t_tokens **tokens)
{
	int	opened;

	if (!(*tokens) || (*tokens)->type != T_O_PAREN)
		return ;
	opened = 0;
	while (*tokens)
	{
		if ((*tokens)->type == T_O_PAREN)
			opened++;
		if ((*tokens)->type == T_C_PAREN)
			opened--;
		(*tokens) = (*tokens)->next;
		if (opened == 0)
			break ;
	}
}

void	syntax_error(void)
{
	write(2, "Syntax error\n", 13);
}
