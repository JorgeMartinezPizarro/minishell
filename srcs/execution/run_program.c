/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:55:03 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 16:31:45 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char	**tokens_to_argv(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		**argv;
	int			len;
	int			i;

	len = 0;
	tmp = tokens;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	argv = ft_calloc(len + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	tmp = tokens;
	while (tmp)
	{
		argv[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return (argv);
}

static int	run_child(t_cmd *com, t_shell *shell, char *exe, char **argv)
{
	setup_signals_child();
	execve(exe, argv, env_list_to_envp(shell->env));
	print_error(com->args->str, "invalid command");
	exit(EXIT_CANT_EXEC);
}

static int	wait_child(pid_t pid)
{
	int	status;

	setup_signals_parent_waiting();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	run_program(t_cmd *com, t_shell *shell)
{
	char	**argv;
	char	*exe;
	pid_t	pid;

	exe = find_executable(com->args->str, com->env);
	if (!exe)
		return (127);
	argv = tokens_to_argv(com->args);
	if (!argv)
		return (free(exe), EXIT_GENERAL_ERROR);
	pid = fork();
	if (pid == -1)
		return (free_str_array(argv), free(exe), free_shell(shell),
			exit(EXIT_GENERAL_ERROR), 0);
	if (pid == 0)
		run_child(com, shell, exe, argv);
	free_str_array(argv);
	free(exe);
	return (wait_child(pid));
}
