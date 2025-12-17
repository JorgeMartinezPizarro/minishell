/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:42:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/17 13:10:37 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	assign_node_type(t_tree **node, t_tokens *token)
{
	if (!token)
		(*node)->n_type = N_CMND;
	else if (token->type == T_OR)
		(*node)->n_type = N_OR;
	else if (token->type == T_AND)
		(*node)->n_type = N_AND;
	else if (token->type == T_PIPE)
		(*node)->n_type = N_PIPE;
}

t_tokens	*division_point(t_tokens *start, t_tokens *end)
{
	t_tokens	*last_or;
	t_tokens	*last_and;
	t_tokens	*last_pipe;

	last_or = NULL;
	last_and = NULL;
	last_pipe = NULL;
	while (start && start != end)
	{
		if (start->type == T_O_PAREN)
			iter_paren(&start);
		if (start->type == T_OR)
			last_or = start;
		if (start->type == T_AND)
			last_and = start;
		if (start->type == T_PIPE)
			last_pipe = start;
		start = start->next;
	}
	if (last_or)
		return (last_or);
	if (last_and)
		return (last_and);
	return (last_pipe);
}

void	remove_paren(t_tree **tree, t_tokens **start, t_tokens **end)
{
	t_tokens	*tmp;
	int			opened;
//si el siguiente del primero es el final
	if ((*start)->next == *end || (*start)->type != T_O_PAREN)
		return ;
	opened = 1;
	(*tree)->subshell = true;
	*start = (*start)->next;
	tmp = *start;
	while (tmp && tmp != *end && opened != 0)
	{
		if ((*start)->type == T_O_PAREN)
			opened++;
		else if ((*start)->type == T_C_PAREN)
			opened--;
		*end = tmp;
		if (opened == 0)
			return ;
		tmp = tmp->next;
	}
}

bool	everything_inside_paren(t_tokens *start, t_tokens *end)
{
	int	opened;

	if (start == end || start->type != T_O_PAREN)
		return (false);
	opened = 1;
	start = start->next;
	while (start && start != end && opened != 0)
	{
		if (start->type == T_O_PAREN)
			opened++;
		else if (start->type == T_C_PAREN)
			opened--;
		if (opened == 0 && start->next == NULL)
			return (true);
		start = start->next;
	}
	return (false);
}
