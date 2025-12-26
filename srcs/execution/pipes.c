/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:51:40 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/27 00:53:02 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	left_pipe(t_tree *node, t_shell **shell, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		perror("fork error");
		free_shell(*shell);
		exit(1);
	}
	if (pid == 0)
	{
		(*shell)->is_child = true;
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_tree(node->left, *shell);
		free_shell(*shell);
		exit(g_exit_code);
	}
	return (pid);
}

static pid_t	right_pipe(t_tree *node, t_shell **shell, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		perror("fork error");
		free_shell(*shell);
		exit(1);
	}
	if (pid == 0)
	{
		(*shell)->is_child = true;
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_tree(node->right, *shell);
		free_shell(*shell);
		exit(g_exit_code);
	}
	return (pid);
}

void	exec_pipe(t_tree *node, t_shell **shell)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		free_shell(*shell);
		exit(1);
	}
	pid_left = left_pipe(node, shell, fd);
	pid_right = right_pipe(node, shell, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_code = 128 + WTERMSIG(status);
}
