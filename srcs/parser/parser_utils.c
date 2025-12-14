/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:35:11 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/14 03:07:17 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_b_op(t_parse *parse, t_token_list *token)
{
	if (!token)
		return ;
	if (token->type == OR)
		parse->or = true;
	else if (token->type == AND)
		parse->and = true;
	//mirar si me viene bien avanzar la lista de tokens cuando hay b_op
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
	while (*tokens)
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

/*
	durante la fase de parsing los errores que se detectan son:

	1 tokens en posiciones ilegales 		| ls
	2 operadores binarios mal colocados		ls &&
	3 
*/
int	invalid_input(t_tree *tree)
{
	
}
