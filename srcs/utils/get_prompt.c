#include "minishell_jorge.h"

///////////////////////////////////////////////////////////////////////////////
// Get bash PC identifier from env.
//	Try to load the 42 variables.
//  Fallback to NAME for regular computers.
//  Otherwise it returns unknown.
///////////////////////////////////////////////////////////////////////////////
char	*get_prompt(t_list *env)
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