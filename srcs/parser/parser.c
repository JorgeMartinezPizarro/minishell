/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:29:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/17 16:32:05 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/*
lo primero que hacer en parse es validar el comando, si no devolver NULL

lo siguiente es gestionar las redirecciones 
*/
void	*parse(t_cmd **node, t_tokens *start, t_tokens *end)
{
	while (start != end)
	{
		if (is_redir(start->type))
		{
			if (!start->next || start->next->type != T_WORD)
				return (syntax_error(), NULL);
			add_redir();
		}
		else
		{
			add_token();
		}
		start = start->next;
	}
}
/*
comprobar estas validaciones:
() → everything_inside_paren → vacío → error
ls && → division_point detecta operador sin derecha
(ls &&) → parse() falla
(ls)(wc) → no hay operador → error
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
		if (!parse(&node, start, end))
			return (free(node), NULL);
		return (node);
	}
	node->left = make_tree(start, div_p);
	node->right = make_tree(div_p->next, NULL);
	if (!node->left || !node->right)
		return (free(node), NULL);//imprimir syntax
	return (node);
}

//Por hacer: parse, division_point, range_empty
/*
0 VALIDACIÓN DE LÍNEA DE TOKENS: validar los casos que no se puedan durante la formación del árbol
	(se puede hacer en la tokenización) ->

1 CREAR Y PARSEAR ÁRBOL: 

VALIDAR INPUT EN HOJAS(parte del parseo)

*/
