/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:35:11 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/13 03:10:01 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_b_op(t_tree **tree, t_token_list *token)
{
	if (!token)
		return ;
	if (token->type == OR)
		(*tree)->or = true;
	else if (token->type == AND)
		(*tree)->and = true;
}

bool	b_op_after_paren(t_token_list *tokens)
{
	int	opened;

	if (!tokens || tokens->type != O_PAREN)
		return ;
	opened = 0;
	while (tokens)
	{
		if (tokens->type == O_PAREN)
			opened++;
		if (tokens->type == C_PAREN)
			opened--;
		if (opened == 0)
			break ;
		tokens = tokens->next;
	}
	return (tokens->type == OR || tokens->type == AND);
}


void	iter_paren(t_token_list **tokens)
{
	int	opened;

	if (!(*tokens) || (*tokens)->type != O_PAREN)
		return ;
	opened = 0;
	while ((*tokens))
	{
		if ((*tokens)->type == O_PAREN)
			opened++;
		if ((*tokens)->type == C_PAREN)
			opened--;
		if (opened == 0)
			break ;
		(*tokens) = (*tokens)->next;
	}
}
