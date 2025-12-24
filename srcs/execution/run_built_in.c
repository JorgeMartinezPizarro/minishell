/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:01:28 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/24 21:34:09 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"
#include <sys/stat.h>

// TODO: hay casos de error a considerar?
int	run_unset(t_cmd *com)
{
	del_env_value(&com->env, com->args->next->str);
	return (EXIT_OK);
}

int	run_built_in(t_cmd *com, t_shell *shell)
{
	if (ft_strcmp(com->args->str, "echo") == 0)
		return (run_echo(com));
	else if (ft_strcmp(com->args->str, "env") == 0)
		return (run_env(com));
	else if (ft_strcmp(com->args->str, "pwd") == 0)
		return (run_pwd(com));
	else if (ft_strcmp(com->args->str, "cd") == 0)
		return (run_cd(com));
	else if (ft_strcmp(com->args->str, "export") == 0)
		return (run_export(com));
	else if (ft_strcmp(com->args->str, "unset") == 0)
		return (run_unset(com));
	else if (ft_strcmp(com->args->str, "exit") == 0)
		return (run_exit(shell));
	else
	{
		ft_printf("bash: command '%s' not found.\n", com->args->str);
		return (EXIT_GENERAL_ERROR);
	}
}

int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}
