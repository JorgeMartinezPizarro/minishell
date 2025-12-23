/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:58:30 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/23 16:32:33 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"
#include "minishell.h"

/*
** Expande variables de entorno en una lista de tokens
*/
void	expand_env_tokens(t_tokens **tokens, t_list *env)
{
	t_tokens	*result;
	t_tokens	*cur;
	t_tokens	*tmp;

	cur = *tokens;
	result = NULL;
	while (cur)
	{
		if ((cur->type == T_WORD || cur->type == T_DOUBLE_QUOTE)
			&& ft_strchr(cur->str, '$'))
		{
			cur->str = expand_vars(cur->str, env);
			t_tokens *t = NULL;
			tokenize(cur->str, &t);
			tmp = t;
			while (t)
			{
				add_token_to_list(&result, t->str, T_WORD);
				t = t->next;
			}
			free_tokens(tmp);
		}
		else
			add_token_to_list(&result, cur->str, cur->type);
		cur = cur->next;
	}
	free_tokens(*tokens);
	*tokens = result;
}
