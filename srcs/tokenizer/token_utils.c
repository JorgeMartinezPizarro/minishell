/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:36:17 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/25 23:55:01 by jomarti3         ###   ########.fr       */
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

bool	valid_paren(char *line)
{
	int	opened;
	int	closed;

	opened = 0;
	closed = 0;
	while (*line)
	{
		if (*line == '(')
			opened++;
		else if (*line == ')')
			closed++;
		if (closed > opened)
			return (false);
		line++;
	}
	if (opened - closed == 0)
		return (true);
	return (false);
}

int	which_operator(char *line)
{
	if (!*line || *line == '\n')
		return (EOF);
	if (!ft_strncmp("<<", line, 2))
		return (T_HEREDOC);
	if (!ft_strncmp(">>", line, 2))
		return (T_APPEND);
	if (!ft_strncmp("&&", line, 2))
		return (T_AND);
	if (!ft_strncmp("||", line, 2))
		return (T_OR);
	if (*line == '>' || *line == '<' || *line == '|' || *line == '('
		|| *line == ')')
		return (*line);
	return (T_WORD);
}

char	*iter_line(char *line)
{
	char	quote;

	if (which_operator(line) > 4)
		line += 1;
	else if (which_operator(line) == T_WORD)
	{
		while (*line != ' ' && which_operator(line) == T_WORD)
		{
			quote = *line;
			if (*line == '\"' || *line == '\'')
				line = ft_strchr(++line, quote);
			line++;
		}
	}
	else if (which_operator(line) != EOF)
		line += 2;
	while (*line == ' ')
		line++;
	if (!*line || *line == '\n')
		return (NULL);
	return (line);
}
