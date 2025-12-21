/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:35:11 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/20 21:56:53 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_redir(t_redir **redirs, t_tokens **token)
{
	t_redir	*new;

	new = ft_calloc(sizeof(t_redir), 1);
	if (!new)
		free_redirs(redirs);
	new->redir_type = (*token)->type;
	*token = (*token)->next;
	add_token_to_list(&new->file, (*token)->str, (*token)->type);
	new->next = NULL;
	if (!redirs || !*redirs)
	{
		*redirs = new;
		return ; 
	}
	while (*redirs)
		*redirs = (*redirs)->next;
	(*redirs)->next = new;
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
