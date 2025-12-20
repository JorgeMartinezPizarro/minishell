/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:58:30 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/20 15:32:55 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"
#include "minishell.h"

/*
** Expande wildcards en una lista de tokens
*/
void	expand_tokens(t_tokens **tokens, char *cwd)
{
	t_tokens	*result;
	t_tokens	*cur;
	char		**expanded;
	int			i;

	cur = *tokens;
	result = NULL;
	while (cur)
	{
		if ((cur->type == T_WORD || cur->type == T_DOUBLE_QUOTE)
			&& ft_strchr(cur->str, '*'))
		{
			expanded = expand_wildcard(cwd, cur->str);
			i = 0;
			while (expanded[i])
				add_token_to_list(&result, expanded[i++], T_WORD);
			free_str_array(expanded);
		}
		else
			token_add_back(&result, token_new(ft_strdup(cur->str), cur->type));
		cur = cur->next;
	}
	free(*tokens);
	*tokens = result;
}
