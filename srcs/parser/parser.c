/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:29:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/15 08:25:04 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_token_list	*copy_left(t_token_list *tokens)
{
	
}

t_token_list	*manage_paren(t_parse *parse, t_token_list *tokens)
{
	t_token_list	*new;
	int				opened;

//si solo hay paréntesis hacer una copia de todo pero sin paréntesis
	if (tokens->type != O_PAREN)
		return (tokens);
	opened = 1;
	tokens = tokens->next;
//si todo está contenido entre paréntesis quitarlos y devolver otra lista de tokens
	while (tokens && opened != 0)
	{
		if (tokens->type == O_PAREN)
			opened++;
		else if (tokens->type == C_PAREN)
			opened--;
		tokens = tokens->next;
	}
}
/*
para la hoja izquierda necesito copiar toda la línea hasta que encuentre un
operador lógico 

igual me viene bien asignar dos listas una para la hoja izquierda y otra para la derecha
copy_left y copy_right

para la hoja izquierda puedo usar la lista tmp
y para la derecha si hay paréntesis hasta que se cierre el paréntesis primero
y luego copiar el resto
*/
t_tree	*make_tree(t_tree **tree, t_token_list *tokens)
{
	t_token_list	*tmp;
	
	*tree = ft_calloc(sizeof(t_tree), 1);
	if (!*tree)
		free_all_exit();//se podría poner un malloc error
	if (!tokens)
		return (free_tree(tree), NULL);
	tmp = manage_paren(&(*tree)->parse, tokens);//si todo está contenido entre paréntesis quitarlos y subproces = true
	if (to_parse(tmp) == true)//parsear si la lista de tmp no tiene paréntesis ni b_op
		parse(&(*tree)->parse, &tmp);//poner tmp = NULL
	(*tree)->left = make_tree(&(*tree)->left, copy_left(tmp));
	set_b_op(&(*tree)->parse, &tmp);
	(*tree)->right = make_tree(&(*tree)->right, tmp);
	return (tree);
}
//Por hacer: manage_paren, to_parse, parse, copy_left, *set_b_op

void	parse(t_parse *parse, t_token_list **tokens)
{
	//aquí creo y asigno la estructura parse 
}

/*
0 VALIDACIÓN DE LÍNEA DE TOKENS: validar los casos que no se puedan durante la formación del árbol
	(se puede hacer en la tokenización) ->

1 CREAR Y PARSEAR ÁRBOL: 

VALIDAR INPUT EN HOJAS(parte del parseo)

*/
