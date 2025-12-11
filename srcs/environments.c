
#include "minishell_jorge.h"
#include "libft.h"

// TODO: write code

/*

t_variable *env is a list of pairs of strings, finished with 
NULL. replace char **env properly.

*/
size_t env_len(char **env)
{
	size_t i;

	i = 0;
	while (*(env++) != NULL)
		i++;
	return i;
}

// add value to env and return the new vars
// free and malloc
t_variable *set_env_value(t_variable *vars, char *name, char *value)
{
    int i = 0;
    // buscar si ya existe la variable
    while (vars && vars[i].name)
    {
        if (ft_strcmp(vars[i].name, name) == 0)
        {
            free(vars[i].value);
            vars[i].value = ft_strdup(value);
            return vars;
        }
        i++;
    }

    // contar elementos existentes
    int count = i;

    // crear nuevo array con espacio para uno más + NULL
    t_variable *new_vars = malloc((count + 2) * sizeof(t_variable));
    if (!new_vars)
        return NULL;

    // copiar los existentes
    for (i = 0; i < count; i++)
    {
        new_vars[i].name = ft_strdup(vars[i].name);
        new_vars[i].value = ft_strdup(vars[i].value);
    }

    // añadir la nueva variable
    new_vars[count].name = ft_strdup(name);
    new_vars[count].value = ft_strdup(value);

    // NULL final
    new_vars[count + 1].name = NULL;
    new_vars[count + 1].value = NULL;

    // liberar array antiguo
    for (i = 0; i < count; i++)
    {
        free(vars[i].name);
        free(vars[i].value);
    }
    free(vars);

    return new_vars;
}

// del a value from env and return the new vars
// free and malloc
t_variable *del_env_value(t_variable *vars, char *name)
{
    if (!vars)
        return NULL;

    int i = 0, j = 0;
    // contar elementos existentes
    while (vars[i].name)
        i++;
    int count = i;

    // crear nuevo array
    t_variable *new_vars = malloc(count * sizeof(t_variable)); // -1 + NULL
    if (!new_vars)
        return NULL;

    for (i = 0, j = 0; i < count; i++)
    {
        if (ft_strcmp(vars[i].name, name) != 0)
        {
            new_vars[j].name = ft_strdup(vars[i].name);
            new_vars[j].value = ft_strdup(vars[i].value);
            j++;
        }
        free(vars[i].name);
        free(vars[i].value);
    }
    free(vars);

    // NULL final
    new_vars[j].name = NULL;
    new_vars[j].value = NULL;

    return new_vars;
}

char *get_env_value(t_variable *vars, char *name)
{
    int i = 0;
    while (vars && vars[i].name)
    {
        if (ft_strcmp(vars[i].name, name) == 0)
            return vars[i].value;
        i++;
    }
    return NULL; // no encontrada
}

// cleanup all env
// free
void free_env(t_variable *vars)
{
    if (!vars)
        return;

    int i = 0;
    while (vars[i].name)
    {
        free(vars[i].name);
        free(vars[i].value);
        i++;
    }
    free(vars);
}

// load static env array into malloc memory
// malloc
t_variable *load_env_values(char **env)
{
    t_variable *var;
    int len;
    int i;
	int j;
	
    len = env_len(env);
    var = malloc((1 + len) * sizeof(t_variable));
    if (!var)
        return NULL;
    i = 0;
    while (*env != NULL)
    {
        char **s = ft_split(*env, '=');
        if (!s || !s[0])
        {
            env++;
            continue;
        }
        var[i].name = ft_strdup(s[0]);
		if (s[1])
        	var[i].value = ft_strdup(s[1]);
		else
			var[i].value = ft_strdup("");
        j = 0;
        while (s[j])
        {
            free(s[j]);
            j++;
        }
        free(s);
        env++;
        i++;
    }

    return var;
}
