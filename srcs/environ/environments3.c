/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:39:12 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/21 12:39:13 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "libft.h"

char	**env_list_to_envp(t_list *env)
{
	int len = ft_lstsize(env);
	char **envp = ft_calloc(len + 1, sizeof(char *));
	t_list *node = env;
	int i = 0;

	while (node)
	{
		t_variable *var = (t_variable *)node->content;
		envp[i] = ft_strjoin(var->name, "=");
		char *tmp = ft_strjoin(envp[i], var->value);
		free(envp[i]);
		envp[i] = tmp;
		node = node->next;
		i++;
	}
	envp[i] = NULL;
	return envp;
}
