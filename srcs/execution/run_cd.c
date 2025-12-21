/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:48:53 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/21 11:51:08 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

static char	*get_cd_target(t_cmd *com)
{
	if (com->args->next == NULL)
		return (expand_vars(ft_strdup("$HOME"), com->env));
	return (expand_vars(ft_strdup(com->args->next->str), com->env));
}

static int	change_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		ft_putstr_fd("Folder does not exist.\n", 2);
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

	target = get_cd_target(com);
	if (!target)
		return (0);
	new_path = join_paths(com->cwd, target);
	free(target);
	if (!new_path)
		return (0);
	if (!change_directory(new_path))
		return (free(new_path), 0);
	set_env_value(&com->env, "OLDPWD", com->cwd);
	set_env_value(&com->env, "PWD", new_path);
	free(com->cwd);
	com->cwd = new_path;
	return (1);
}
