/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:25:29 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/26 16:55:59 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	left_pipe(t_tree *node, t_shell **shell, int *fd)
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
		free_shell(*shell);
		exec_tree(node->left, *shell);
		exit(g_exit_code);
	}
}

static void	right_pipe(t_tree *node, t_shell **shell, int *fd)
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
}

void	exec_pipe(t_tree *node, t_shell **shell)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		free_shell(*shell);
		exit(1);
	}
	left_pipe(node, shell, fd);
	right_pipe(node, shell, fd);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
