/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:05:14 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/12 11:51:51 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "libft.h"

static t_list *build_var_formats(const char *var)
{
    t_list *formats = NULL;
    char *tmp;
    char *s;

    // $VAR
    tmp = ft_strjoin("$", var);
    ft_lstadd_back(&formats, ft_lstnew(tmp));

    // ${VAR}
    tmp = ft_strjoin("${", var);
    s = ft_strjoin(tmp, "}");
    free(tmp);
    ft_lstadd_back(&formats, ft_lstnew(s));

    return formats;
}

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
            value = ""; // reemplazar por cadena vacía si no existe

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