/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:55:03 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/24 23:40:21 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char	*find_executable(const char *cmd, t_list *env)
{
	char	*path_env;
	char	**dirs;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return NULL;
	}
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full = join_paths(dirs[i], cmd);
		if (access(full, X_OK) == 0)
		{
			free_str_array(dirs);
			return (full);
		}
		free(full);
		i++;
	}
	free_str_array(dirs);
	return (NULL);
}

static char **tokens_to_argv(t_tokens *tokens)
{
	t_tokens	*tmp;
	char 		**argv;
	int 		len;
	int 		i;

	len = 0;
	i = 0;
	tmp = tokens;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	argv = ft_calloc(len + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	tmp = tokens;
	while (tmp)
	{
		argv[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	argv[i] = (NULL);
	return (argv);
}
/*
queremos crear un proceso nuevo y 
	NOTE: fijate aqui como manejo las signals para que solo control C lo coja el
	shell actual. 
*/
int	run_program(t_cmd *com, t_shell *shell)
{
	char	**argv;
	char	*exe;
	int		status;
	pid_t	pid;

	exe = find_executable(com->args->str, com->env);
	if (!exe)
		return (ft_printf("%s: command not found\n", com->args->str), 127);
	argv = tokens_to_argv(com->args);
	if (!argv)
		return (free(exe), EXIT_GENERAL_ERROR);
	pid = fork();
	if (pid == -1)
		return (free_str_array(argv), free(exe), free_shell(shell),
			exit(EXIT_GENERAL_ERROR), 0);
	if (pid == 0)
	{
		setup_signals_child();
		execve(exe, argv, env_list_to_envp(shell->env));
		perror("execve");
		exit(EXIT_CANT_EXEC);
	}
	free_str_array(argv);
	free(exe);
	setup_signals_parent_waiting();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
