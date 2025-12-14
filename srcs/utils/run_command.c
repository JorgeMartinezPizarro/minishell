/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:46:52 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/14 19:37:40 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"

// TODO: Cada comando es un fichero por separado.

// TODO: echo puede tener >> o > en cuyo caso debe volcarse a fichero en vez de 
// imprimirlo en el fd 1.
int run_echo(t_command *com)
{
	if (com->argc < 2)
	{	
		ft_printf("What to echo?");
		return 0;
	}
	ft_printf("%s\n", expand_vars(ft_strreplace(com->args[1], "\n", ""), com->env));
	return 1;
}

int run_env(t_command *com)
{
    t_list *node;

	node = com->env;
    while (node)
    {
        t_variable *v = (t_variable *)node->content;
        ft_printf("%s=%s\n", v->name, v->value);
        node = node->next;
    }
    return 1;
}

int run_pwd(t_command *com)
{
	ft_printf("%s\n", com->cwd);
	return 1;
}

// TODO
// Actualizar OLDPWD en los env para mantener coherencia. 
// Revisar si el directorio existe antes de hacer cd!
int	run_cd(t_command *com)
{
	char *new_path = join_paths(com->cwd, expand_vars(ft_strreplace(com->args[1], "\n", ""), com->env));
	set_env_value(&com->env, "PWD", new_path);
	com->cwd = ft_strdup(new_path);
	return 1;
}

// TODO: validar la sintaxis, export a=1 sin espacios, como en shell
int run_export(t_command *com)
{
	char **item = ft_split(ft_strreplace(com->args[1], "\n", ""), '=');
	set_env_value(&com->env, item[0], item[1]);
	return 1;
}

// TODO: tecnicamente, a=1 funciona como export a=1
int run_set(t_command *com)
{
	char **item = ft_split(com->command, '=');
	set_env_value(&com->env, item[0], item[1]);
	return 1;
}

// TODO: error si la variable no existe
int run_unset(t_command *com)
{
	del_env_value(&com->env, ft_strreplace(com->args[1], "\n", ""));
	return 1;
}

// TODO: Hay mas codigos de error?
// return 1 => true, 0 => false
// TODO: Tenemos que considerar si el comando es el nombre de un ejecutable.
int run_command(t_command *com)
{
	if (ft_strcmp(com->command, "echo") == 0)
		return run_echo(com);
	else if (ft_strcmp(com->command, "env") == 0)
		return run_env(com);
	else if (ft_strcmp(com->command, "pwd") == 0)
		return run_pwd(com);
	else if (ft_strcmp(com->command, "cd") == 0)
		return run_cd(com);
	else if (ft_strcmp(com->command, "export") == 0)
		return run_export(com);
	else if (ft_strcmp(com->command, "unset") == 0)
		return run_unset(com);
	else if (ft_strchr(com->command, '=') != NULL)
		return run_set(com);
	else {
		ft_printf("What do you mean with '%s'?\n", com->command);
		return 0;
	}
}