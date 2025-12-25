/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:28:58 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 16:30:54 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

static int	run_with_env(t_tokens *t, t_list *t_env, t_shell *shell, t_cmd *com)
{
	t_cmd	new_cmd;
	t_shell	new_shell;

	new_cmd.args = t;
	new_cmd.env = t_env;
	new_cmd.redirs = com->redirs;
	new_shell.env = t_env;
	new_shell.first_node = shell->first_node;
	new_shell.is_child = false;
	if (is_built_in(t->str))
		return (run_built_in(&new_cmd, &new_shell));
	else
		return (run_program(&new_cmd, &new_shell));
}

///////////////////////////////////////////////////////////////////////////////
//
// a=15 b=15 comando
// 		ejecuta comando con a en el env, 
// 		pero no setea a ni b en el entorno actual.
// a=15
// 		si agrega a al env como export.
// export A=15 B=15
// 		las agrega al env actual.
//
// Metacodigo (split assign from export)
//
// assign:
//
//  haz un clone de env
//	por cada token con =, haz la asignacion en el clone
//  si llegamos a NULL, cambiamos el clone env con env.
//	si llegamos a un comando, lanzamos el comando con el clone.
//
///////////////////////////////////////////////////////////////////////////////
int	run_assign(t_cmd *com, t_shell *shell)
{
	char		**item;
	t_tokens	*t;
	t_list		*tmp_env;
	char		*name;
	char		*value;

	tmp_env = clone_env(com->env);
	t = com->args;
	while (t && ft_strchr(t->str, '=') != NULL)
	{
		item = ft_split(t->str, '=');
		name = item[0];
		value = ft_strchr(t->str, '=');
		set_env_value(&tmp_env, name, ++value);
		free_str_array(item);
		t = t->next;
	}
	if (t)
		return (run_with_env(t, tmp_env, shell, com));
	com->env = tmp_env;
	return (EXIT_OK);
}
