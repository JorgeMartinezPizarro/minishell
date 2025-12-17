/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:01:02 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/16 21:34:18 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"

static int	is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}

static int	get_var_range(const char **p, const char **start, const char **end)
{
	if (**p == '{')
	{
		(*p)++;
		*start = *p;
		while (**p && **p != '}')
			(*p)++;
		if (**p != '}')
			return (0);
		*end = *p;
		(*p)++;
		return (1);
	}
	if (is_var_char(**p))
	{
		*start = *p;
		while (is_var_char(**p))
			(*p)++;
		*end = *p;
		return (1);
	}
	return (0);
}

static int	add_var(t_list **vars, const char *start, const char *end)
{
	char	*var;
	size_t	len;

	len = end - start;
	var = malloc(len + 1);
	if (!var)
		return (0);
	ft_strlcpy(var, start, len + 1);
	ft_lstadd_back(vars, ft_lstnew(var));
	return (1);
}

t_list	*extract_variables(const char *str)
{
	t_list		*vars;
	const char	*p;
	const char	*start;
	const char	*end;

	vars = NULL;
	p = str;
	while (*p)
	{
		if (*p == '$')
		{
			p++;
			if (get_var_range(&p, &start, &end))
			{
				if (!add_var(&vars, start, end))
				{
					ft_lstclear(&vars, free);
					return (NULL);
				}
			}
		}
		else
			p++;
	}
	return (vars);
}
