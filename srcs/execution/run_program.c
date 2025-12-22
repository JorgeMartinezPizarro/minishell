/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:55:03 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/22 12:40:05 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char *find_executable(const char *cmd)
{
	char *path_env;
	char **dirs;
	char *full;
	int i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
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
int	run_program(t_cmd *com, t_shell *shell)
{
	char	**argv;
	char	*exe;
	int		status;
	pid_t	pid;

	exe = find_executable(com->args->str);
	if (!exe)
		return (ft_printf("%s: command not found\n", com->args->str), 127);
	argv = tokens_to_argv(com->args);
	if (!argv)
		return (free(exe), 1);
	pid = fork();
	if (pid == -1)
		return (1);//liberar shell
	if (pid == 0)
	{
		execve(exe, argv, env_list_to_envp(shell->env));
		perror("execve");
		exit(126);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
