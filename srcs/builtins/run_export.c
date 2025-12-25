/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:28:58 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 16:20:17 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

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
int	run_export(t_cmd *com)
{
	char		**item;
	t_tokens	*t;
	char		*name;
	char		*value;

	if (com->args->next == NULL)
	{
		print_sorted_env(com->env);
		return (EXIT_OK);
	}
	t = com->args->next;
	while (t)
	{
		item = ft_split(t->str, '=');
		name = item[0];
		value = ft_strchr(t->str, '=');
		if (value == NULL)
			set_env_value(&com->env, name, "");
		else
			set_env_value(&com->env, name, ++value);
		free_str_array(item);
		t = t->next;
	}
	return (EXIT_OK);
}
