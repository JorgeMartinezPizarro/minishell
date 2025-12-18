/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:36:53 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/18 16:38:26 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "minishell.h"


void	exec_pipe(t_tree *tree)
{
	pid_t	pids[2];
	int		fd[2];

	if (pipe(fd) == -1)
		(perror("pipe error"), exit(1));
	pids[0] = fork();
	if (pids[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(close(fd[0]), close(fd[1]));
		exec_tree(tree->left);
		exit(exit_status);
	}
	pids[1] = fork();
	if (pids[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(close(fd[0]), close(fd[1]));
		exec_tree(tree->right);
		exit(exit_status);
	}
	(close(fd[0]), close(fd[1]));
	(wait(NULL), wait(NULL));
}

void	exec_b_op(t_tree *tree, e_node_type type)
{
	// Para que compile
	(void)type;
	if (tree->n_type == N_OR)
	{
		exec_tree(tree->left);
		if (exit_status != 0)
			exec_tree(tree->right);
	}
	if (tree->n_type == N_AND)
	{
		exec_tree(tree->left);
		if (exit_status == 0)
			exec_tree(tree->right);
	}
}

void	exec_subprocces(t_tree **tree)
{
	pid_t	pid;

	if ((*tree)->subshell == true)
	{
		pid = fork();
		if (pid == 0)
		{
//hacer una copia de env(puede que ya la herede directamente y no haga falta)
			// Estoy gestionando las variables de entorno en el cmd,
			// aqui podemos hacer un clone para que no afecten al hijo.
			(*tree)->subshell = false;
			exec_tree(*tree);
			exit(exit_status);
		}
		wait(NULL);
	}
}

void	exec_tree(t_tree *tree)
{
	exec_subprocces(&tree);
	if (tree->n_type == N_PIPE)
		exec_pipe(tree);
	if (tree->n_type == N_OR || tree->n_type == N_AND)
		exec_b_op(tree, tree->n_type);
	if (tree->n_type == N_CMND)
	{
		// He juntado mi t_command dentro de tu t_cmd.
		// Requiere inicializar el env, mira en main_test.c
		// Aqui se puede usar cmd->env = clone_env(cmd->env)
		// para procesos hijos
		if (is_built_in(tree->cmd))
			tree->cmd->exit_code = run_built_in(tree->cmd);
		else
			tree->cmd->exit_code = run_program(tree->cmd);
	}
}
