/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:58:30 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/18 13:03:14 by jomarti3         ###   ########.fr       */
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
	t_tokens	*cur;
	char		**expanded;
	int			i;

	result = NULL;
	cur = tokens;
	while (cur)
	{
		if (cur->type == T_WORD && ft_strchr(cur->str, '*'))
		{
			expanded = expand_wildcard(cwd, cur->str);
			i = 0;
			while (expanded[i])
			{
				token_add_back(&result,
					token_new(ft_strdup(expanded[i]), T_WORD));
				i++;
			}
			i = 0;
			while (expanded[i])
				free(expanded[i++]);
			free(expanded);
		}
		else
		{
			token_add_back(&result,
				token_new(ft_strdup(cur->str), cur->type));
		}
		cur = cur->next;
	}
	return (result);
}