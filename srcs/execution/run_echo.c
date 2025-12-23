/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:52:15 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/23 22:20:26 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

int is_echo_n(const char *s)
{
    int i;

    if (!s || s[0] != '-' || s[1] != 'n')
        return 0;

    i = 2;
    while (s[i])
    {
        if (s[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

int run_echo(t_cmd *com)
{
    t_tokens    *temp;
    int         no_newline;
    int         first;

	no_newline = 0;
    first = 1;
    temp = com->args->next;
    while (temp && is_echo_n(temp->str))
    {
        no_newline = 1;
        temp = temp->next;
    }
    while (temp)
    {
        if (!first)
            ft_printf(" ");
        ft_printf("%s", temp->str);
        first = 0;
        temp = temp->next;
    }
    if (!no_newline)
        ft_printf("\n");
    return (EXIT_OK);
}
