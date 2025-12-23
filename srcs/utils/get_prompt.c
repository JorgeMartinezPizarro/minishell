#include "minishell_jorge.h"

///////////////////////////////////////////////////////////////////////////////
// Get bash PC identifier from env.
//	Try to load the 42 variables.
//  Fallback to NAME for regular computers.
//  Otherwise it returns unknown.
///////////////////////////////////////////////////////////////////////////////
static char	*get_name(t_list *env)
{
	char **vals;
	char **its;
	char **els;
	char *sol;
	char *var;

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
	char *str;
	char *head;
	char *name;
	char *tmp;

	str = ft_strdup("\001\033[1;33m${USER}@#### >>> \033[0m\002");
	head = expand_vars(str, env);
	name = get_name(env);
	tmp = head;
	head = ft_strreplace(tmp, "####", name);
	free(tmp);
	free(name);
	return (head);
}

