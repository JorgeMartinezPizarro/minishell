/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:29:57 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/06 01:48:11 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_quotes(char *line)
{
	while (*line)
	{
		if (*line == '\"')
			line = ft_strchr(++line, '\"');
		else if (*line == '\'')
			line = ft_strchr(++line, '\'');
		if (!line)
			return (0);
		line++;
	}
	return (1);
}

int	which_operator(char *line)
{
	if (!ft_strncmp("<<", line, 2))
		return (HEREDOC);
	if (!ft_strncmp(">>", line, 2))
		return (APPEND);
	if (!ft_strncmp("&&", line, 2))
		return (AND);
	if (!ft_strncmp("||", line, 2))
		return (OR);
	if (*line == '>' || *line == '<' || *line == '|')
		return (*line);
	return (0);
}

/*
1 añadir al final de la lista un nuevo nodo
2 
*/
void	add_token(t_token_list *tokens, char *str, int type)
{
	t_token_list *new_token;

	new_token = malloc(sizeof(t_token_list));
	if (!new_token)
		free_and_exit();
	if (type == WORD)
		;
	else if (type <= 4)
		new_token->str = ft_substr(str, 0, 2);
	else
		new_token->str = ft_substr(str, 0, 1);
	new_token->type = type;
}

/*
iter_line cambia la dirección de memoria de line y si no hay nada después *line = 0
identifica el elemento actual, cuanto avanzar dependiendo de su longitud y
si es el último **line = 0

Ejemplo: avanzar dos si el actual es >> y si el elemento actual es el último
marcar el caracter actual como '\0' y salir del bucle
*/
void	iter_line(char **line)
{

}

/*
esta función devuelve un array de tokens y cuya estructura
será una estructura será un string y el tipo de token que es
(el tipo de token se puede añadir al tener todo separado)

add_quotes copia el contenido hasta la siguiente comilla y su tipo
de token puede ser comilla doble o simple para luego expandir o no

add_space añade un espacio(tipo space o word)cuando hay algún elemento
después el cual no sea un espacio

add_operator un operador (el tipo depende de qué operador sea)

add_word añade un string expandible(tipo word) hasta el siguiente ' ' o operador
*/

int	tokenize(char *line, t_token_list *tokens)
{
	if (!valid_quotes(line))
		return (0);
	//iter_line para ignorar espacios iniciales
	iter_line(&line);
	while (*line)
	{
		if (is_quote(*line))
			line = add_quotes(line, tokens);
		else if (which_operator(line))
			add_operator(line, tokens);
		else if (*line == ' ')//no hay que gestionar tabs y viceversa
			add_space(" ", tokens);
		else
			add_word(line, tokens);
		iter_line(&line);
	}
	return (1);
}
