/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:58:30 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/20 15:05:32 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"

static t_tokens	*token_new(char *str, int type)
{
	t_tokens	*tok;

	tok = ft_calloc(1, sizeof(t_tokens));
	if (!tok)
		return (NULL);
	tok->str = str;
	tok->type = type;
	return (tok);
}

/*
** Añadir token al final
*/
static void	token_add_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/*
** Expande wildcards en una lista de tokens
*/
t_tokens	*expand_tokens(t_tokens *tokens, char *cwd)
{
	t_tokens	*result;
	char		**expanded;
	int			i;

	result = NULL;
	while (tokens)
	{
		if ((tokens->type == T_WORD || tokens->type == T_DOUBLE_QUOTE)
			&& ft_strchr(tokens->str, '*'))
		{
			expanded = expand_wildcard(cwd, tokens->str);
			i = 0;
			while (expanded[i])
			{
				token_add_back(&result,
					token_new(ft_strdup(expanded[i]), T_WORD));
				i++;
			}
			free_str_array(expanded);
		}
		else
			token_add_back(&result, token_new(ft_strdup(tokens->str), tokens->type));
		tokens = tokens->next;
	}
	return (result);
}
