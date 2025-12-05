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

/*	identifica qué operador es y lo añade a la estructura
	primero compara con los operadores multicaracter y luego
	los de un caracter
	
*/
void	add_operator(char *line, t_tokens_line *tokenized_line)
{
	
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

add_until_space añade un string expandible(tipo word) hasta el siguiente ' '
*/

int	tokenize(char *line, t_tokens_line *tokenized_line)
{
	if (!valid_quotes(line))
		return (0);
	//iter_line para ignorar espacios iniciales
	iter_line(&line);
	while (*line)
	{
		if (is_quote(*line))
			line = add_quotes(line, tokenized_line);
		else if (is_operator(line))
			add_operator(line, tokenized_line);
		else if (*line == ' ')//no hay que gestionar tabs y viceversa
			add_space(tokenized_line);
		else
			add_until_space(line, tokenized_line);
		iter_line(&line);
	}
	return (1);
}
