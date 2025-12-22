/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:58:30 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/22 18:12:29 by jomarti3         ###   ########.fr       */
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
			add_token_to_list(&result, cur->str, cur->type);
		cur = cur->next;
	}
	free(cwd);
	free_tokens(*tokens);
	*tokens = result;
}
