/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:52:15 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/21 11:54:55 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

// TODO: Ojo con -n, -nnnnn
int	run_echo(t_cmd *com)
{
	t_tokens	*temp;

	temp = com->args->next;
	if (temp)
	{
		temp->str = expand_vars(temp->str, com->env);
		ft_printf("%s", temp->str);
	}
	else
		return (1);
	temp = temp->next;
	while (temp)
	{
		temp->str = expand_vars(temp->str, com->env);
		ft_printf(" %s", temp->str);
		temp = temp->next;
	}
	ft_printf("\n");
	return (1);
}
