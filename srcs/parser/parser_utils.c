/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:35:11 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/17 14:00:12 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(t_tokens *token)
{
	if (token->type == T_APPEND || token->type == T_HEREDOC
		|| token->type == T_REDIR_IN || token->type == T_REDIR_OUT)
		return (true);
	return (false);
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
