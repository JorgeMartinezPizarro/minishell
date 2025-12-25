/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:58:30 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 19:08:54 by maanguit         ###   ########.fr       */
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
	t_tokens 	*t;

	cur = *tokens;
	result = NULL;
	while (cur)
	{
		if (ft_strchr(cur->str, '$'))
		{
			cur->str = expand_vars(cur->str, env);
			t = NULL;
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
