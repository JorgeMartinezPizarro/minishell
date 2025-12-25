/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:58:30 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 19:20:49 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"
#include "minishell.h"

/*
** Expande wildcards en una lista de tokens
*/
void	expand_wildcard_tokens(t_tokens **tokens, char *cwd)
{
	t_tokens	*result;
	t_tokens	*cur;
	char		**expanded;
	int			i;

	cur = *tokens;
	result = NULL;
	while (cur)
	{
		if (ft_strchr(cur->str, '*'))
		{
			expanded = expand_wildcard(cwd, cur->str);
			i = 0;
			while (expanded[i])
				add_token_to_list(&result, expanded[i++], T_WORD);
			free_str_array(expanded);
		}
		else
			add_token_to_list(&result, cur->str, cur->type);
		cur = cur->next;
	}
	free_tokens(*tokens);
	*tokens = result;
}
