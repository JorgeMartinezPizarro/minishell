/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:48:53 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 01:28:07 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

static char	*get_cd_target(t_cmd *com)
{
	if (com->args->next == NULL || ft_strcmp(com->args->next->str, "~") == 0)
		return (get_env_value(com->env, "HOME"));
	else if (ft_strcmp(com->args->next->str, "-") == 0)
	{
		ft_printf("%s\n", get_env_value(com->env, "OLDPWD"));
		return (get_env_value(com->env, "OLDPWD"));
	}
	return (com->args->next->str);
}

static int	change_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		ft_putstr_fd("cd: folder not found\n", 2);
		return (0);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (0);
	}
	return (1);
}

int	run_cd(t_cmd *com)
{
	char	*target;
	char	*new_path;
	char	*old;

	if (com->args->next && com->args->next->next)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (EXIT_GENERAL_ERROR);
	}
	old = get_env_value(com->env, "PWD");
	target = get_cd_target(com);
	if (!target)
		return (EXIT_GENERAL_ERROR);
	new_path = join_paths(old, target);
	if (!new_path)
		return (EXIT_GENERAL_ERROR);
	if (!change_directory(new_path))
		return (free(new_path), EXIT_GENERAL_ERROR);
	set_env_value(&com->env, "OLDPWD", old);
	set_env_value(&com->env, "PWD", new_path);
	free(new_path);
	return (EXIT_OK);
}
