/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:46:52 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/18 10:21:40 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_jorge.h"
#include <sys/stat.h>

// TODO: Cada comando es un fichero por separado.

// TODO: echo puede tener >> o > en cuyo caso debe volcarse a fichero en vez de 
// imprimirlo en el fd 1.
int run_echo(t_command *com)
{
	t_tokens *temp;

	temp = com->args;
	if (temp)
		ft_printf("%s", expand_vars(temp->str, com->env));
	temp = temp->next;
	while (temp){
		ft_printf(" %s", expand_vars(temp->str, com->env));
		temp = temp->next;
	}

	ft_printf("\n");
	
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

int run_cd(t_command *com)
{
    char *new_path;
    struct stat st;

	new_path = join_paths(com->cwd, expand_vars(com->args->str, com->env));
    if (stat(new_path, &st) != 0)
    {
        ft_putstr_fd("Folder does not exist\n", 2);
        free(new_path);
        return 0;
    }
	if (chdir(new_path) != 0)
    {
        perror("cd");
        free(new_path);
        return 0;
    }
    set_env_value(&com->env, "OLDPWD", com->cwd);
    set_env_value(&com->env, "PWD", new_path);
    free(com->cwd);
    com->cwd = ft_strdup(new_path);
    free(new_path);
    return (1);
}

// TODO: validar la sintaxis, export a=1 sin espacios, como en shell
int run_export(t_command *com)
{
	char **item = ft_split(com->args->str, '=');
	set_env_value(&com->env, item[0], item[1]);
	return 1;
}

// TODO: tecnicamente, a=1 funciona como export a=1
// En efecto NO, los comandos marcados con export se pasan
// a los procesos hijos con execev.
int run_set(t_command *com)
{
	char **item = ft_split(com->command, '=');
	set_env_value(&com->env, item[0], item[1]);
	return 1;
}

// TODO: error si la variable no existe
int run_unset(t_command *com)
{
	del_env_value(&com->env, com->args->str);
	return 1;
}



// TODO: Hay mas codigos de error?
// return 1 => true, 0 => false
// TODO: Tenemos que considerar si el comando es el nombre de un ejecutable, buscando el comando
// en cada ruta de la variable PATH. Hacemos split by : y buscamos si el fichero existe
// Si existe se ejecuta!
int run_built_in(t_command *com)
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
		ft_printf("Command '%s' not found.\n", com->command);
		return 0;
	}
}

int is_built_in(char *str)
{
	if (
		   ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strchr(str, '=') != NULL
	)
		return (1);
	return 0;
}