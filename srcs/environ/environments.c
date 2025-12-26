/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:34:42 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 20:00:34 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "libft.h"

size_t	strarr_len(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

size_t	env_len_list(t_list *vars)
{
	return (ft_lstsize(vars));
}

static int	add_env_var(t_list **vars, char *env_line)
{
	t_variable	*v;
	char		*eq;

	eq = ft_strchr(env_line, '=');
	if (!eq)
		return (0);
	v = malloc(sizeof(t_variable));
	if (!v)
		return (-1);
	v->name = ft_substr(env_line, 0, eq - env_line);
	v->value = ft_strdup(eq + 1);
	v->exported = 1;
	if (!v->name || !v->value)
		return (free_variable(v), -1);
	ft_lstadd_back(vars, ft_lstnew(v));
	return (0);
}

t_list	*load_env_values(char **env)
{
	t_list	*vars;

	vars = NULL;
	while (*env)
	{
		if (add_env_var(&vars, *env) < 0)
		{
			free_env(&vars);
			return (NULL);
		}
		env++;
	}
	return (vars);
}
