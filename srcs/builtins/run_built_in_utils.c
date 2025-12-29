/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:53:55 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/29 15:21:21 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!((name[0] >= 'A' && name[0] <= 'Z')
			|| (name[0] >= 'a' && name[0] <= 'z')
			|| name[0] == '_' ))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= '0' && name[i] <= '9')
				|| name[i] == '_' ))
			return (0);
		i++;
	}
	return (1);
}

int	run_unset(t_cmd *com)
{
	t_tokens	*t;
	int			status;

	t = com->args->next;
	status = EXIT_OK;
	while (t)
	{
		if (!is_valid_identifier(t->str))
		{
			print_error(t->str, "invalid identifier");
			status = EXIT_GENERAL_ERROR;
		}
		else
			del_env_value(&com->env, t->str);
		t = t->next;
	}
	return (status);
}

int	run_env(t_cmd *com)
{
	t_list		*node;
	t_variable	*v;

	node = com->env;
	while (node)
	{
		v = (t_variable *)node->content;
		if (v->assigned)
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

int	run_exit(t_cmd *com, t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	if (com->args->next && !ft_valid_int(com->args->next->str))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		free_shell(shell);
		exit(2);
	}
	if (com->args->next && com->args->next->next)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (EXIT_GENERAL_ERROR);
	}
	if (shell->is_child == false)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (com->args->next)
		exit_code = ft_atoi(com->args->next->str) & 0xFF;
	free_shell(shell);
	exit(exit_code);
}
