/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:29:22 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/11 05:13:10 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/*
como gestionar el parser?

1 validar el input de tokens
	1 mirar como funciona la shell y ver como empiezar a construir la lógica 
2 agrupar los tokens en un arbol cuya hoja sea cada línea de comandos
	1 separar por líneas de comandos 
	2 conocer todos los tokens que delimitan cada orden

El objetivo es un arbol binario en el que cada hoja sea una línea de instrucciones.

Dentro de cada hoja queremos tener separados los datos dependiendo de donde se redirijan
	
*/

int	invalid_input(t_parsed_line *parsed_line)
{
	
}

//esta función agrupa los tokens en execution_lines por ejemplo: cat < infile | echo hola && tac < infile
//hasta el && sería un string y después del && otro
void	join_tokens(t_parsed_line **parsed_line, t_token_list *tokens)
{
	
}//función para el bonus

int	parse(t_parsed_line **parsed_line, t_token_list *tokens)
{
	join_tokens(parsed_line, tokens);
	free_tokens(tokens);
// una vez unidos los tokens unir los elementos resultantes de join_tokens

	
	if (invalid_input(parsed_line))//esto se ejecuta durante la ejecución, no en el parseo
		return (write(2, "Invalid input"), 0);
}
