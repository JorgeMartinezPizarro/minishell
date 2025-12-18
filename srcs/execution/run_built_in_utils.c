/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:53:55 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/18 22:10:44 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

// Print only T_WORD
int	run_cd(t_cmd *com)
{
	char		*new_path;
	struct stat	st;

	new_path = join_paths(com->cwd, expand_vars(com->args->next->str, com->env));
	if (stat(new_path, &st) != 0)
	{
		ft_putstr_fd("Folder does not exist.\n", 2);
		free(new_path);
		return 0;
	}
	if (chdir(new_path) != 0)
	{
		perror("cd");
		free(new_path);
		return 0;
	}
	set_env_value(&com->env, "OLDPWD", com->cwd);
	set_env_value(&com->env, "PWD", new_path);
	free(com->cwd);
	com->cwd = ft_strdup(new_path);
	free(new_path);
	return (1);
}

// Print only T_WORD
int run_echo(t_cmd *com)
{
	t_tokens *temp;

	temp = com->args->next;
	if (temp)
		ft_printf("%s", expand_vars(temp->str, com->env));
	temp = temp->next;
	while (temp){
		ft_printf(" %s", expand_vars(temp->str, com->env));
		temp = temp->next;
	}
	ft_printf("\n");
	return (1);
}

int run_env(t_cmd *com)
{
	t_list *node;

	node = com->env;
	while (node)
	{
		t_variable *v = (t_variable *)node->content;
		ft_printf("%s=%s\n", v->name, v->value);
		node = node->next;
	}
	return 1;
}

int run_pwd(t_cmd *com)
{
	ft_printf("%s\n", com->cwd);
	return 1;
}
