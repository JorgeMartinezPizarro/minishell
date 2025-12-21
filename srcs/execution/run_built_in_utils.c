/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:53:55 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/21 12:12:13 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

int	run_env(t_cmd *com)
{
	t_list		*node;
	t_variable	*v;

	node = com->env;
	while (node)
	{
		v = (t_variable *)node->content;
		ft_printf("%s=%s\n", v->name, v->value);
		node = node->next;
	}
	return (1);
}

int	run_pwd(t_cmd *com)
{
	(void)com;
	ft_printf("%s\n", getcwd(NULL, 0));
	return (1);
}

// TODO: discutir con mangit como gestionar esto desde exec_tree
int	run_exit(t_cmd *com)
{
	(void)com;
	return (1);
}
