/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:29:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/18 13:54:05 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/minishell_jorge.h"

void	*parse_cmd(t_tree **node, t_tokens *start, t_tokens *end)
{
	(*node)->cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!(*node)->cmd)
		return (NULL);
	while (start != end)
	{
		if (!is_redir(start->type) && start->type != T_WORD)//puede que esto joda algo por ejemplo: $()
			return (free_cmnd((*node)->cmd), NULL);
		if (is_redir(start->type))
		{
			if (start->next == end || start->next->type != T_WORD)
				return (free_cmnd((*node)->cmd), NULL);
			add_redir(&(*node)->cmd->redirs, &start);
		}
		else if (start->type == T_WORD)
			add_token_to_list(&(*node)->cmd->args, start->str, T_WORD);
		start = start->next;
	}
	if (!(*node)->cmd->args)
		return (free_cmnd((*node)->cmd), NULL);
	(*node)->cmd->is_builtin = is_built_in((*node)->cmd->args->str);
	return (&(*node)->cmd);
}
/*
comprobar estas validaciones:
() → everything_inside_paren → vacío → error
ls && → division_point detecta operador sin derecha
(ls &&) → parse() falla
(ls)(wc) → no hay operador → error (creo que este no lo gestiona el árbol)

en este caso la función devuelve NULL y al no haber ningún elemento

&& ls → división inválida
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
	assign_node_type(node, div_p);
	if (node->n_type == N_CMND)
	{
		if (!parse_cmd(&node, start, end))
			return (free(node), syntax_error(), NULL);
		return (node);
	}
	node->left = make_tree(start, div_p);
	node->right = make_tree(div_p->next, NULL);
	if (!node->left || !node->right)
		return (free(node), syntax_error(), NULL);
	return (node);
}

