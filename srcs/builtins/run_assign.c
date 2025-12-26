/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:28:58 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 02:39:06 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

static int	assign_one(t_list **env, char *arg)
{
	char	*eq;
	char	*name;

	eq = ft_strchr(arg, '=');
	name = ft_substr(arg, 0, eq - arg);
	if (!is_valid_identifier(name))
		return (print_error(name, "invalid identifier"),
			free(name), EXIT_GENERAL_ERROR);
	set_env_value(env, name, eq + 1, 0);
	free(name);
	return (EXIT_OK);
}

static int	run_with_env(t_tokens *t, t_list *t_env, t_shell *shell, t_cmd *com)
{
	t_cmd	new_cmd;
	t_shell	new_shell;
	int		status;

	new_cmd.args = t;
	new_cmd.env = t_env;
	new_cmd.redirs = com->redirs;
	new_shell.env = t_env;
	new_shell.first_node = shell->first_node;
	new_shell.is_child = false;
	if (is_built_in(t->str))
		status = run_built_in(&new_cmd, &new_shell);
	else
		status = run_program(&new_cmd, &new_shell);
	free_env(&t_env);
	return (status);
}

int	run_assign(t_cmd *com, t_shell *shell)
{
	t_tokens	*t;
	t_list		*tmp_env;

	tmp_env = clone_env(com->env);
	t = com->args;
	while (t && ft_strchr(t->str, '='))
	{
		if (assign_one(&tmp_env, t->str) != EXIT_OK)
			return (free_env(&tmp_env), EXIT_GENERAL_ERROR);
		t = t->next;
	}
	if (t)
		return (run_with_env(t, tmp_env, shell, com));
	if (shell->env != com->env)
		free_env(&com->env);
	com->env = tmp_env;
	return (EXIT_OK);
}
