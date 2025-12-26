/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:42:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/26 22:50:36 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_tokens	*last_b_op;
	t_tokens	*last_pipe;

	last_b_op = NULL;
	last_pipe = NULL;
	while (start && start != end)
	{
		if (start->type == T_O_PAREN)
			iter_paren(&start);
		if (!start)
			break ;
		if (start->type == T_OR || start->type == T_AND)
			last_b_op = start;
		if (start->type == T_PIPE)
			last_pipe = start;
		start = start->next;
	}
	if (last_b_op)
		return (last_b_op);
	return (last_pipe);
}

t_tokens	*remove_paren(t_tree **tree, t_tokens **start, t_tokens *end)
{
	t_tokens	*tmp;
	int			opened;

	if ((*start)->next == end || (*start)->type != T_O_PAREN)
		return (end);
	opened = 1;
	(*tree)->subshell = true;
	*start = (*start)->next;
	tmp = *start;
	while (tmp && tmp != end && opened != 0)
	{
		if (tmp->type == T_O_PAREN)
			opened++;
		else if (tmp->type == T_C_PAREN)
			opened--;
		if (opened == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
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
		if (opened == 0 && start->next == end)
			return (true);
		start = start->next;
	}
	return (false);
}
