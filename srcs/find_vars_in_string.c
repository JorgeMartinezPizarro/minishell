/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_vars_in_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:01:02 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/10 14:12:16 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"

static char *extract_var(const char *s, size_t *len)
{
    size_t i;

    if (s[1] == '?')
    {
        *len = 2;
        return (ft_strdup("?"));
    }
    i = 1;
    if (!ft_isalpha(s[i]) && s[i] != '_')
    {
        *len = 1;
        return (NULL);
    }
    while (ft_isalnum(s[i]) || s[i] == '_')
        i++;
    *len = i;
    return (ft_substr(s, 1, i - 1));
}

static char **push_var(char **arr, char *var)
{
    int     n;
    char  **new;

    n = 0;
    while (arr && arr[n])
        n++;
    new = malloc(sizeof(char *) * (n + 2));
    if (!new)
        return (NULL);
    for (int i = 0; i < n; i++)
        new[i] = arr[i];
    new[n] = var;
    new[n + 1] = NULL;
    free(arr);
    return (new);
}

char **find_vars_in_string(char *str)
{
    char    **vars;
    size_t   len;
    char    *v;

    vars = NULL;
    while (*str)
    {
        if (*str == '$')
        {
            v = extract_var(str, &len);
            if (v)
                vars = push_var(vars, v);
            str += len;
        }
        else
            str++;
    }
    return (vars);
}
