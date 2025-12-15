/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:01:02 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/15 01:38:58 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"

// TODO: arreglar este desastre. $(VAR) no es valido en shell,
// $VAR o ${VAR}. Ajustar a la norma.
t_list *extract_variables(const char *str)
{
    t_list *vars = NULL;
    const char *p = str;

    while (*p)
    {
        if (*p == '$')
        {
            p++;
            const char *start = NULL;
            const char *end = NULL;

            if (*p == '{' || *p == '(')  // ${VAR} o $(VAR)
            {
                char close = (*p == '{') ? '}' : ')';
                p++; // saltar { o (
                start = p;

                while (*p && *p != close)
                    p++;

                end = p;
                if (*p == close)
                    p++; // saltar } o )
            }
            else if ((*p >= '0' && *p <= '9') || (*p >= 'A' && *p <= 'Z') ||
                     (*p >= 'a' && *p <= 'z') || *p == '_')
            {
                start = p;
                while ((*p >= '0' && *p <= '9') || (*p >= 'A' && *p <= 'Z') ||
                       (*p >= 'a' && *p <= 'z') || *p == '_')
                    p++;
                end = p;
            }

            if (start && end && end > start)
            {
                size_t len = end - start;
                char *var = malloc(len + 1);
                if (!var)
                {
                    ft_lstclear(&vars, free);
                    return NULL;
                }
                ft_strlcpy(var, start, len + 1); // copia segura + terminación
                ft_lstadd_back(&vars, ft_lstnew(var));
            }
        }
        else
            p++;
    }

    return vars;
}
