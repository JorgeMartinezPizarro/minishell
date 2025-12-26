/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:28:58 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 22:46:43 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_one(t_cmd *com, char *arg)
{
	char	*eq;
	char	*name;

	eq = ft_strchr(arg, '=');
	if (eq)
		name = ft_substr(arg, 0, eq - arg);
	else
		name = ft_strdup(arg);
	if (!is_valid_identifier(name))
		return (print_error(name, "invalid identifier"),
			free(name), EXIT_GENERAL_ERROR);
	if (eq)
		set_env_value(&com->env, name, eq + 1, 1);
	else
		set_env_value(&com->env, name, "", 1);
	free(name);
	return (EXIT_OK);
}

int	run_export(t_cmd *com)
{
	t_tokens	*t;
	int			status;

	if (com->args->next == NULL)
		return (print_sorted_env(com->env), EXIT_OK);
	t = com->args->next;
	status = EXIT_OK;
	while (t)
	{
		if (export_one(com, t->str) != EXIT_OK)
			status = EXIT_GENERAL_ERROR;
		t = t->next;
	}
	return (status);
}
