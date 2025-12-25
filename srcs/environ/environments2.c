/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:22:47 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 00:33:55 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"

static void	*dup_env_var(void *content)
{
	t_variable	*v;
	t_variable	*copy;

	v = (t_variable *)content;
	copy = malloc(sizeof(t_variable));
	if (!copy)
		return (NULL);
	copy->name = ft_strdup(v->name);
	copy->value = ft_strdup(v->value);
	if (!copy->name || !copy->value)
	{
		free(copy->name);
		free(copy->value);
		free(copy);
		return (NULL);
	}
	return (copy);
}

t_list	*clone_env(t_list *env)
{
	return (ft_lstclone(env, dup_env_var));
}

char	*get_env_value(t_list *vars, char *name)
{
	t_variable	*v;

	while (vars)
	{
		v = (t_variable *)vars->content;
		if (ft_strcmp(v->name, name) == 0)
			return (v->value);
		vars = vars->next;
	}
	return (NULL);
}

void	set_env_value(t_list **vars, char *name, char *value)
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
	ft_lstadd_back(vars, ft_lstnew(v_new));
}

void	del_env_value(t_list **vars, char *name)
{
	t_list		*prev;
	t_list		*curr;
	t_variable	*v;

	prev = NULL;
	curr = *vars;
	while (curr)
	{
		v = (t_variable *)curr->content;
		if (ft_strcmp(v->name, name) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*vars = curr->next;
			free(v->name);
			free(v->value);
			free(v);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
