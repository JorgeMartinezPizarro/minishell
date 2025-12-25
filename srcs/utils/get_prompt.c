/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:40:21 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 15:41:23 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

char	*get_color(t_list *env)
{
	char	*str;

	str = get_env_value(env, "COLOR");
	if (!str)
		return ("\033[0m");
	if (ft_strcmp(str, "BLACK") == 0)
		return ("\033[0;30m");
	else if (ft_strcmp(str, "RED") == 0)
		return ("\033[0;31m");
	else if (ft_strcmp(str, "GREEN") == 0)
		return ("\033[0;32m");
	else if (ft_strcmp(str, "YELLOW") == 0)
		return ("\033[0;33m");
	else if (ft_strcmp(str, "BLUE") == 0)
		return ("\033[0;34m");
	else if (ft_strcmp(str, "MAGENTA") == 0)
		return ("\033[0;35m");
	else if (ft_strcmp(str, "CYAN") == 0)
		return ("\033[0;36m");
	else if (ft_strcmp(str, "WHITE") == 0)
		return ("\033[0;37m");
	return ("\033[0m");
}

///////////////////////////////////////////////////////////////////////////////
// Get bash PC identifier from env.
//	Try to load the 42 variables.
//  Fallback to NAME for regular computers.
//  Otherwise it returns unknown.
///////////////////////////////////////////////////////////////////////////////
static char	*get_name(t_list *env)
{
	char	**vals;
	char	**its;
	char	**els;
	char	*sol;
	char	*var;

	var = get_env_value(env, "SESSION_MANAGER");
	if (!var)
	{
		var = get_env_value(env, "NAME");
		if (!var)
			return (ft_strdup("unknown"));
		return (ft_strdup(var));
	}
	vals = ft_split(var, ':');
	its = ft_split(vals[0], '.');
	els = ft_split(its[0], '/');
	sol = ft_strdup(els[1]);
	free_str_array(vals);
	free_str_array(its);
	free_str_array(els);
	return (sol);
}

///////////////////////////////////////////////////////////////////////////////
// Usando \001 y \002 permitimos a readline calcular el ancho de linea.
// Los otros codigos ANSI son para darle color.
// 
// EXTRA: permitir via ENV cambiar el color?
///////////////////////////////////////////////////////////////////////////////
char	*get_prompt(t_list *env)
{
	char	*str;
	char	*head;
	char	*name;
	char	*tmp;

	str = ft_strdup("\001XXXXX\002${USER}@#### >>> \001\033[0m\002");
	head = expand_vars(str, env);
	name = get_name(env);
	tmp = head;
	head = ft_strreplace(tmp, "####", name);
	free(tmp);
	tmp = head;
	head = ft_strreplace(tmp, "XXXXX", get_color(env));
	free(tmp);
	free(name);
	return (head);
}
