/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:05:14 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/10 14:07:11 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "libft.h"

static char *build_key(const char *name)
{
    char    *key;
    int     len;

    len = ft_strlen(name);
    key = malloc(len + 2);
    if (!key)
        return (NULL);
    key[0] = '$';
    ft_memcpy(key + 1, name, len);
    key[len + 1] = '\0';
    return (key);
}

char    *expand_vars(const char *s, char **env)
{
    char    **vars;
    char    *res;
    char    *key;
    char    *val;
    int     i;

    if (!s)
        return (NULL);
    res = ft_strdup(s);
    vars = find_vars_in_string(res);
    if (!vars)
        return (res);
    i = 0;
    while (vars[i])
    {
        key = build_key(vars[i]);
        val = get_env_value(env, vars[i]);
        if (!val)
            val = "";
        res = ft_strreplace(res, key, val);
        free(key);
        free(vars[i]);
        i++;
    }
    free(vars);
    return (res);
}