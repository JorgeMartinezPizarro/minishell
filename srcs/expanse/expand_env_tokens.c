/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:58:30 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 21:18:01 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"
#include "minishell.h"

static void	process_token(t_tokens *cur, t_tokens **result, t_list *env)
{
	t_tokens	*t;
	t_tokens	*tmp;

	cur->str = expand_vars(cur->str, env);
	t = NULL;
	tokenize(cur->str, &t);
	tmp = t;
	while (t)
	{
		add_token_to_list(result, t->str, T_WORD);
		t = t->next;
	}
	free_tokens(tmp);
}

void	expand_env_tokens(t_tokens **tokens, t_list *env)
{
	t_tokens	*result;
	t_tokens	*cur;

	cur = *tokens;
	result = NULL;
	while (cur)
	{
		if (ft_strchr(cur->str, '$'))
			process_token(cur, &result, env);
		else
			add_token_to_list(&result, cur->str, cur->type);
		cur = cur->next;
	}
	free_tokens(*tokens);
	*tokens = result;
}
