/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:23:49 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/26 12:38:44 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_shell(t_shell *shell)
{
	free_tree(shell->first_node);
	free_env(&shell->env);
	free(shell);
}
