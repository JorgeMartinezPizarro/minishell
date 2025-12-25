/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:55:03 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 15:22:07 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

static void	print_error(const char *str1, const char *str2)
{
	ft_putstr_fd((char *)str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)str2, 2);
	ft_putstr_fd("\n", 2);
}

char	*find_executable(const char *cmd, t_list *env)
{
	char	*path_env;
	char	**dirs;
	char	*full;
	int		i;
	struct stat st;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) != 0)
			return (print_error(cmd, "file not found"), NULL);
		if (!S_ISREG(st.st_mode))
			return (print_error(cmd, "file not found"), NULL);
		if (access(cmd, X_OK) != 0)
			return (print_error(cmd, "permission denied"), NULL);
		return (ft_strdup(cmd));
	}

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (print_error(cmd, "command not found"), NULL);

	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);

	i = 0;
	while (dirs[i])
	{
		full = join_paths(dirs[i], cmd);
		if (stat(full, &st) == 0 && S_ISREG(st.st_mode) && access(full, X_OK) == 0)
		{
			free_str_array(dirs);
			return (full);
		}
		free(full);
		i++;
	}

	free_str_array(dirs);
	print_error(cmd, "command not found");
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
		return (127);
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
		print_error(com->args->str, "invalid command");
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
