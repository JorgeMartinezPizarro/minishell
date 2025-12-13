/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:29:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/13 06:05:32 by maanguit         ###   ########.fr       */
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

/*
(cmd && cmd) -> indicar que es un subproceso y cada comando a una rama
(    &&    ) -> al entrar aquí ya estamos dentro de un subproceso
cmd     cmd  -> se ejecutan el primero y si funciona, el segundo

1 mirar si operador después de el paréntesis -> DESPUÉS declaramos subprocces = true, quitamos el paréntesis y ahora se comprueba si hay operador (paso 2)
2 si hay operador va a la rama izquierda todo lo anterior al operador
3 si no hay operador se parsea en la hoja actual

Un subproceso solo se declara cuando no hay operadores fuera del paréntesis

La condición para ejecutar una hoja es que no hay más hojas a su izquierda
*/
void	make_tree(t_tree **tree, t_token_list *tokens)
{
	(*tree)->parse = NULL;
	create_and_assign_left_leaf(tree, tokens);
	right_leaf(tree, tokens);
	set_b_op(tree, tokens);
	
	//si hay operador lógico se asigna a la hoja actual
}
/*
si no hay b_op se parsea todo en la hoja actual -> se parsea todo

si hay b_op 2 opciones
	1 dentro de paren
	2 fuera -> se copia el paréntesis a hoja izquierda

si hay paréntesis se parsea 
si no hay paréntesis se parsea hasta el b_op en la hoja actual

necesito una función que me copie todo el contenido de los paréntesis incluidos
una función que itere paréntesis
una función que me diga si hay paréntesis y si después hay operador

*/

int	parse(t_tree **tree, t_token_list *tokens)
{
	make_tree(tree, tokens);
	free_tokens(tokens);
	
	if (invalid_input(tree))//guardar si es válido para la ejecución
		return (write(2, "Invalid input\n", 15), 0);
}

/*
0 VALIDACIÓN DE LÍNEA DE TOKENS: validar los casos que no se puedan durante la formación del árbol
	(se puede hacer en la tokenización)

1 CREAR ARBOL: si tokens && o || entonces hasta && al nodo izquierdo, && al actual y el resto al nodo derecho

2 PARSEAR ARBOL: 

3 VALIDAR INPUT EN HOJAS

creación y parseo en etapas distintas? creo que lo mejor es hacer el parseo con los datos existentes

como crear el arbol a la vez que le pones sus datos?   solo hace falta saber por donde va del tokenizer

*/
