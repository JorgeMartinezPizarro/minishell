/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:01:28 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/19 13:28:48 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"
#include <sys/stat.h>

// TODO: Cada comando es un fichero por separado.
// TODO: echo puede tener >> o > en cuyo caso debe volcarse a fichero en vez de 
// imprimirlo en el fd 1.
// TODO: validar la sintaxis, export a=1 sin espacios, como en shell
int	run_export(t_cmd *com)
{
	char	**item;

	item = ft_split(com->args->next->str, '=');
	set_env_value(&com->env, item[0], item[1]);
	return (1);
}

// TODO: tecnicamente, a=1 funciona como export a=1
// En efecto NO, los comandos marcados con export se pasan
// a los procesos hijos con execev.
int	run_set(t_cmd *com)
{
	char	**item;

	item = ft_split(com->args->str, '=');
	set_env_value(&com->env, item[0], item[1]);
	return (1);
}

// TODO: error si la variable no existe
int	run_unset(t_cmd *com)
{
	del_env_value(&com->env, com->args->next->str);
	return (1);
}

// TODO: Hay mas codigos de error?
// return 1 => true, 0 => false
// TODO: Tenemos que considerar si el comando es el nombre de un ejecutable
// buscando el comando
// en cada ruta de la variable PATH. Hacemos split by : y buscamos si el 
// fichero existe
// Si existe se ejecuta!

// TODO: add exit!
int	run_built_in(t_cmd *com)
{
	if (ft_strcmp(com->args->str, "echo") == 0)
		return (run_echo(com));
	else if (ft_strcmp(com->args->str, "env") == 0)
		return (run_env(com));
	else if (ft_strcmp(com->args->str, "pwd") == 0)
		return (run_pwd(com));
	else if (ft_strcmp(com->args->str, "cd") == 0)
		return (run_cd(com));
	else if (ft_strcmp(com->args->str, "export") == 0)
		return (run_export(com));
	else if (ft_strcmp(com->args->str, "unset") == 0)
		return (run_unset(com));
	else if (ft_strchr(com->args->str, '=') != NULL)
		return (run_set(com));
	else
	{
		ft_printf("Command '%s' not found.\n", com->args->str);
		return (0);
	}
}

int	is_built_in(t_cmd *com)
{
	if (
		ft_strcmp(com->args->str, "echo") == 0
		|| ft_strcmp(com->args->str, "env") == 0
		|| ft_strcmp(com->args->str, "pwd") == 0
		|| ft_strcmp(com->args->str, "cd") == 0
		|| ft_strcmp(com->args->str, "export") == 0
		|| ft_strcmp(com->args->str, "unset") == 0
		|| ft_strchr(com->args->str, '=') != NULL
	)
		return (1);
	return (0);
}
