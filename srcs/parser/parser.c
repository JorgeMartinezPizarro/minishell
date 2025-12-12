/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:29:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/12 03:32:21 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
/*
	durante la fase de parsing los errores que se detectan son:

	1 tokens en posiciones ilegales 		| ls
	2 operadores binarios mal colocados		ls &&
	3 
*/
int	invalid_input(t_tree *tree)
{
	
}

//esta función agrupa los tokens en execution_lines ejemplo: cat < infile | echo hola && tac < infile
void	make_tree(t_tree **tree, t_token_list *tokens)
{
	
}

int	parse(t_tree **tree, t_token_list *tokens)
{
	make_tree(tree, tokens);
	free_tokens(tokens);
	
	if (invalid_input(tree))//guardar si es válido para la ejecución
		return (write(2, "Invalid input"), 0);
}

/*
1 CREAR ARBOL: si tokens && o || entonces hasta && al nodo izquierdo, && al actual y el resto al nodo derecho

2 PARSEAR ARBOL: 

3 VALIDAR INPUT EN HOJAS

creación y parseo en etapas distintas? creo que lo mejor es hacer el parseo con los datos existentes

como crear el arbol a la vez que le pones sus datos?   solo hace falta saber por donde va del tokenizer

*/
