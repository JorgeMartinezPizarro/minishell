/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:05:14 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/23 22:36:33 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "libft.h"

static t_list	*build_var_formats(const char *var)
{
	t_list	*formats;
	char	*tmp;
	char	*s;

	formats = NULL;
	tmp = ft_strjoin("$", var);
	ft_lstadd_back(&formats, ft_lstnew(tmp));
	tmp = ft_strjoin("${", var);
	s = ft_strjoin(tmp, "}");
	free(tmp);
	ft_lstadd_back(&formats, ft_lstnew(s));
	return (formats);
}

static char	*apply_var_formats(char *s, char *var_name, char *value)
{
	t_list	*formats;
	t_list	*fnode;
	char	*new_s;

	formats = build_var_formats(var_name);
	fnode = formats;
	while (fnode)
	{
		new_s = ft_strreplace(s, (char *)fnode->content, value);
		free(s);
		s = new_s;
		fnode = fnode->next;
	}
	ft_lstclear(&formats, free);
	
	return (s);
}

static char	*expand_exit_code(char *s)
{
	char *tmp = s;

	s = ft_strreplace(tmp, "$?", ft_itoa(exit_code));
	free(tmp);
	tmp = s;
	s = ft_strreplace(tmp, "${?}", ft_itoa(exit_code));
	return s;
}

char	*expand_vars(char *s, t_list *env)
{
	t_list	*vars;
	t_list	*node;
	char	*value;

	if (!s)
		return (NULL);
	vars = extract_variables(s);
	node = vars;
	while (node)
	{
		value = get_env_value(env, (char *)node->content);
		if (!value)
			value = "";
		s = apply_var_formats(s, node->content, value);
		node = node->next;
	}
	ft_lstclear(&vars, free);
	return (expand_exit_code(s));
}
