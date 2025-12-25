/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:04:24 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/25 19:20:32 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "minishell.h"

char	*trim_quotes(char *s)
{
	char	*res;
	char	quote;
	int		i;
	int		j;
	
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (perror("malloc error"), NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else
			res[j++] = s[i];
		i++;
	}
	res[j] = '\0';
	free(s);
	return (res);
}

void	mark_dollars(char *s, char mark)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	while (s && s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else if (s[i] == '$' && quote == '\'')
			s[i] = mark;
		i++;
	}
}

void	restore_dollars(char *s, char mark)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == mark)
			s[i] = '$';
		i++;
	}
}
