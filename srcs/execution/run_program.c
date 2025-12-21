/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:55:03 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/21 11:57:09 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char	**env_list_to_envp(t_list *env)
{
	int len = ft_lstsize(env);
	char **envp = ft_calloc(len + 1, sizeof(char *));
	t_list *node = env;
	int i = 0;

	while (node)
	{
		t_variable *var = (t_variable *)node->content;
		envp[i] = ft_strjoin(var->name, "=");
		char *tmp = ft_strjoin(envp[i], var->value);
		free(envp[i]);
		envp[i] = tmp;
		node = node->next;
		i++;
	}
	envp[i] = NULL;
	return envp;
}

char *find_executable(const char *cmd)
{
	char *path_env;
	char **dirs;
	char *full;
	int i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		return NULL;
	}

	path_env = getenv("PATH");
	if (!path_env)
		return NULL;

	dirs = ft_split(path_env, ':');
	if (!dirs)
		return NULL;

	i = 0;
	while (dirs[i])
	{
		full = join_paths(dirs[i], cmd);
		if (access(full, X_OK) == 0)
		{
			free_str_array(dirs);
			return full;
		}
		free(full);
		i++;
	}

	free_str_array(dirs);
	return NULL; // no se encontró
}

static char **tokens_to_argv(t_tokens *tokens)
{
	int len = 0;
	t_tokens *tmp = tokens;
	char **argv;
	int i = 0;

	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}

	argv = ft_calloc(len + 1, sizeof(char *));
	if (!argv)
		return NULL;

	tmp = tokens;
	while (tmp)
	{
		argv[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return argv;
}
/*
queremos crear un proceso nuevo y 
*/
int	run_program(t_cmd *com, char **env)
{
	char	**argv;
	char	*exe;
	int		status;
	pid_t	pid;

	if (!com->args->str)
		return (1);
	exe = find_executable(com->args->str);
	if (!exe)
		return (ft_printf("%s: command not found\n", com->args->str), 127);
	argv = tokens_to_argv(com->args);
	if (!argv)
		return (free(exe), 1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		execve(exe, argv, env_list_to_envp(env));
		perror("execve");
		exit(126);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
