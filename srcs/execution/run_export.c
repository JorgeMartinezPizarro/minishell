/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:28:58 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/24 21:08:45 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"


//
// a=15 comando ejecuta comando con a en el env, pero no setea a
// a=15         si agrega a al env como export.
// export A=15 la agrega al env y la pasa a cada hijo.
int	run_export(t_cmd *com)
{
	char	**item;

	if (com->args->next == NULL)
	{
		print_sorted_env(com->env);
		return (EXIT_OK);
	}
	//print_tokens(com->args);
	item = ft_split(com->args->next->str, '=');
	if (strarr_len(item) == 2)
		set_env_value(&com->env, item[0], item[1]);
	else
	{
		ft_putstr_fd("bash: invalid expression\n", 2);
		return (EXIT_GENERAL_ERROR);
	}
	free_str_array(item);
	return (EXIT_OK);
}