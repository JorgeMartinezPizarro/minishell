/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:01:28 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/23 22:19:31 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"
#include <sys/stat.h>

int	run_export(t_cmd *com)
{
	char	**item;
	// Caso sin variables, parecido a env. Gestionarlo a parte.
	// Las variables deben mostrarse alfabeticamente ordenadas.
	if (com->args->next == NULL)
		return run_env(com, "declare -x ");
	item = ft_split(com->args->next->str, '=');
	// Caso regular, todo en un token, A=15
	if (strarr_len(item) == 2)
		set_env_value(&com->env, item[0], item[1]);
	// Caso raro, dos tokens: export A="echo hola"
	else if (strarr_len(item) == 1 && com->args->next->next) 
		set_env_value(&com->env, item[0], com->args->next->next->str);
	free_str_array(item);
	return (EXIT_OK);
}

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
		return (run_env(com, ""));
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
