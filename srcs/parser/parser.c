/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:29:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/21 15:04:39 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell_jorge.h"

void	*parse_cmd(t_tree **node, t_tokens *start, t_tokens *end)
{
	(*node)->cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!(*node)->cmd)
		return (perror("malloc"), NULL);
	while (start != end)
	{
		if (is_redir(start))
		{
			if (start->next == end || !is_string(start->next))
				return (free_cmnd((*node)->cmd), NULL);
			add_redir(&(*node)->cmd->redirs, &start);
		}
		else if (is_string(start))
			add_token_to_list(&(*node)->cmd->args, start->str, start->type);
		else
			return (free_cmnd((*node)->cmd), NULL);
		start = start->next;
	}
	if (!(*node)->cmd->args)
		return (free_cmnd((*node)->cmd), NULL);
	(*node)->cmd->is_builtin = is_built_in((*node)->cmd->args->str);
	return (&(*node)->cmd);
}

/*
comprobar estas validaciones:
&& ls → división inválida
() → everything_inside_paren → vacío → error
ls && → division_point detecta operador sin derecha
(ls &&) → parse() falla
(ls)(wc) → no hay operador → error (creo que este no lo gestiona el árbol)
*/
t_tree	*make_tree(t_tokens *start, t_tokens *end)
{
	t_tokens	*div_p;
	t_tree		*node;

	if (!start || start == end)
		return (NULL);
	while (everything_inside_paren(start, end))
		remove_paren(&node, &start, &end);
	if (!start || start == end)
		return (NULL);
	node = ft_calloc(sizeof(t_tree), 1);
	if (!node)
		return (perror("malloc error"), NULL);
	div_p = division_point(start, end);
	assign_node_type(&node, div_p);
	if (node->n_type == N_CMND)
	{
		if (!parse_cmd(&node, start, end))
			return (free(node), NULL);
		return (node);
	}
	node->left = make_tree(start, div_p);
	node->right = make_tree(div_p->next, end);
	if (!node->left || !node->right)
		return (free(node), NULL);
	return (node);
}
