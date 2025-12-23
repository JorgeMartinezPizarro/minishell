/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:53:55 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/24 00:06:30 by maanguit         ###   ########.fr       */
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
