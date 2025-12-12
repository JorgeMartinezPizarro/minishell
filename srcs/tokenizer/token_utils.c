/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:36:17 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/12 20:46:57 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

bool	valid_quotes(char *line)
{
	while (*line)
	{
		if (*line == '\"')
			line = ft_strchr(++line, '\"');
		else if (*line == '\'')
			line = ft_strchr(++line, '\'');
		if (!line)
			return (false);
		line++;
	}
	return (true);
}

int	which_operator(char *line)
{
	if (!*line || *line == '\n')
		return (EOF);
	if (!ft_strncmp("<<", line, 2))
		return (HEREDOC);
	if (!ft_strncmp(">>", line, 2))
		return (APPEND);
	if (!ft_strncmp("&&", line, 2))
		return (AND);
	if (!ft_strncmp("||", line, 2))
		return (OR);
	if (*line == '>' || *line == '<' || *line == '|' || *line == '('
		|| *line == ')' || *line == '\"' || *line == '\'')
		return (*line);
	return (WORD);
}

/*
iter_line cambia la dirección de memoria de line

si dependiendo del tipo de operador avanza 1 o 2 posiciones y cuando no es un
operador avanza hasta que encuentre otro operador

si el tipo actual es WORD recorre hasta un espacio

si contenido de línea es espacio los recorre hasta el siguiente elemento

si solo hay espacios después de recorrer el elemento actual devuelve NULL
*/
char	*iter_line(char *line)
{
	char	quote;
	int		type;

	quote = *line;
	if (*line == '\"' || *line == '\'')
		line = ft_strchr(++line, quote);
	type = which_operator(line);
	if (type > 4)
		line += 1;
	else if (type == WORD)
		while (*line != ' ' && which_operator(line) == WORD)
			line++;
	else if (type != EOF)
		line += 2;
	while (*line == ' ')
		line++;
	if (!*line || *line == '\n')
		return (NULL);
	return (line); 
}

void	print_tokens(t_token_list *tokens)
{
	while (tokens)
	{
		printf("content: %s\n", tokens->str);
		printf("type: %d\n", tokens->type);
		tokens = tokens->next;
	}
}

void	free_and_exit(t_token_list *tokens)
{
	t_token_list	*tmp;

	while (tokens)
	{
		tmp = tokens;
		free(tokens->str);
		tokens = tokens->next;
		free(tmp);
	}
	perror("malloc error");
	exit(1);
}
