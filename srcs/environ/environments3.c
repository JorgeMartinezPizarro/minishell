/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:39:12 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/29 14:14:16 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_list_to_envp(t_list *env)
{
	t_variable	*var;
	t_list		*node;
	char		**envp;
	char		*tmp;
	int			i;

	i = 0;
	node = env;
	envp = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	while (node)
	{
		var = (t_variable *)node->content;
		envp[i] = ft_strjoin(var->name, "=");
		tmp = ft_strjoin(envp[i], var->value);
		free(envp[i]);
		envp[i] = tmp;
		node = node->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	update_minishell_level(t_list **env)
{
	char	*str;
	char	*nbr;
	int		i;

	str = get_env_value(*env, "MSHLVL");
	if (!str)
		nbr = ft_strdup("1");
	else
	{
		i = ft_atoi(str) + 1;
		nbr = ft_itoa(i);
	}
	set_env_value(env, "MSHLVL", nbr, 1);
	free(nbr);
}

void	init_required_env(t_list **env)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!get_env_value(*env, "PWD"))
		set_env_value(env, "PWD", str, 1);
	if (!get_env_value(*env, "OLDPWD"))
		set_env_value(env, "OLDPWD", str, 1);
	free(str);
}

void	set_env_value_declare(t_list **vars, char *name, char *value
	, int exported)
{
	t_list		*node;
	t_variable	*v;
	t_variable	*v_new;

	node = *vars;
	while (node)
	{
		v = (t_variable *)node->content;
		if (ft_strcmp(v->name, name) == 0)
		{
			free(v->value);
			v->value = ft_strdup(value);
			return ;
		}
		node = node->next;
	}
	v_new = malloc(sizeof(t_variable));
	v_new->name = ft_strdup(name);
	v_new->value = ft_strdup(value);
	v_new->exported = exported;
	v_new->assigned = false;
	ft_lstadd_back(vars, ft_lstnew(v_new));
}
