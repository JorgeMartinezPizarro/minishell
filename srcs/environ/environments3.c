/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:39:12 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 16:21:41 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "libft.h"

char	**env_list_to_envp(t_list *env)
{
	t_variable	*var;
	t_list		*node;
	char		**envp;
	char		*tmp;
	int			i;

	i = 0;
	node = env;
	envp = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	while (node)
	{
		var = (t_variable *)node->content;
		envp[i] = ft_strjoin(var->name, "=");
		tmp = ft_strjoin(envp[i], var->value);
		free(envp[i]);
		envp[i] = tmp;
		node = node->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
