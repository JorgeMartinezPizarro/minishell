/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:53:55 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 00:18:13 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

// TODO: hay casos de error a considerar?
int	run_unset(t_cmd *com)
{
	del_env_value(&com->env, com->args->next->str);
	return (EXIT_OK);
}

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
	return (EXIT_OK);
}

int	run_pwd(t_cmd *com)
{
	(void)com;
	ft_printf("%s\n", get_env_value(com->env, "PWD"));
	return (EXIT_OK);
}

int	run_exit(t_shell *shell)
{
	if (shell->is_child == false)
		ft_putendl_fd("exit", STDIN_FILENO);
	free_shell(shell);
	exit(EXIT_OK);
}
