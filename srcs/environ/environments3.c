/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:39:12 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/24 01:15:20 by maanguit         ###   ########.fr       */
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
	int			len;
	int			i;

	i = 0;
	node = env;
	len = ft_lstsize(env);
	envp = ft_calloc(len + 1, sizeof(char *));
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
