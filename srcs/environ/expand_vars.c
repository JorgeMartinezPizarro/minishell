/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:05:14 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/20 15:05:23 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "libft.h"

static t_list *build_var_formats(const char *var)
{
	t_list *formats;
	char *tmp;
	char *s;

	formats = NULL;
	tmp = ft_strjoin("$", var);
	ft_lstadd_back(&formats, ft_lstnew(tmp));
	tmp = ft_strjoin("${", var);
	s = ft_strjoin(tmp, "}");
	free(tmp);
	ft_lstadd_back(&formats, ft_lstnew(s));
	return (formats);
}

// TODO: Quizas sea demasiado AGRO hacer free del s, quizas no queramos 
// que el comando que expandimos mute, ademas, esto nos fuerza
// a usar strdup.
char *expand_vars(char *s, t_list *env)
{
	if (!s)
		return NULL;
	t_list *vars = extract_variables(s);
	t_list *node = vars;
	while (node)
	{
		char *var_name = (char *)node->content;
		char *value = get_env_value(env, var_name);
		if (!value)
			value = "";
		t_list *formats = build_var_formats(var_name);
		t_list *fnode = formats;
		while (fnode)
		{
			char *format = (char *)fnode->content;
			char *new_s = ft_strreplace(s, format, value);
			free(s);
			s = new_s;
			fnode = fnode->next;
		}
		ft_lstclear(&formats, free);
		node = node->next;
	}
	ft_lstclear(&vars, free);
	return s;
}
