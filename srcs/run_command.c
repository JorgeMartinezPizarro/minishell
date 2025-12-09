/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:46:52 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/10 00:46:53 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"

int run_echo(t_command *com)
{
	if (com->argc < 2)
	{	
		ft_printf("What to echo?");
		return 0;
	}
	ft_printf("%s\n", com->args[1]);
	return 1;
}

int	run_env(t_command *com)
{
	for (char **p = com->env; *p != NULL; p++) {
		ft_printf("%s\n", *p);
    }
    return 1;
}

// return 1 => true, 0 => false
int run_command(t_command *com)
{
	if (ft_strcmp(com->command, "echo") == 0)
		return run_echo(com);
	else if (ft_strcmp(com->command, "env") == 0)
		return run_env(com);
	else {
		ft_printf("What do you mean?\n");
		return 0;
	}
}