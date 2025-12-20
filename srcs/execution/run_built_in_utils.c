/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:53:55 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/20 21:09:56 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

// Print only T_WORD
int	run_cd(t_cmd *com)
{
	struct stat	st;
	char		*cwd;
	char		*new_path;
	char		*str_exp;

	if (com->args->next == NULL)
		str_exp = expand_vars(ft_strdup("$HOME"), com->env);
	else
		str_exp = expand_vars(ft_strdup(com->args->next->str), com->env);
		//solo expandir si es T_WORD O T_DOUBLE_QUOTE
	getcwd(cwd, 0);
	new_path = join_paths(cwd, str_exp);
	free(str_exp);
	if (stat(new_path, &st) != 0)
		return (ft_putstr_fd("Folder does not exist.\n", 2), free(new_path), 0);
	if (chdir(new_path) != 0)
		return (perror("cd"), free(new_path), 0);
	set_env_value(&com->env, "OLDPWD", cwd);
	set_env_value(&com->env, "PWD", new_path);
	return (1);
}

// Print only T_WORD
// Ojo con -n, -nnnnn
int run_echo(t_cmd *com)
{
	t_tokens	*temp;

	temp = com->args->next;
	if (temp)
	{
		temp->str = expand_vars(temp->str, com->env);
		ft_printf("%s", temp->str);
	}
	else
		return 1;
	temp = temp->next;
	while (temp){
		temp->str = expand_vars(temp->str, com->env);
		ft_printf(" %s", temp->str);
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
	ft_printf("%s\n", getcwd(NULL, 0));
	return 1;
}

int	run_exit(t_cmd *com)
{
	(void)com;
	return 1;
}