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


void	exec_pipe(t_tree *tree, t_list *env)
{
	pid_t	pids[2];
	int		fd[2];

	if (pipe(fd) == -1)
		(perror("pipe error"), exit(1));
	pids[0] = fork();//gestionar el caso de error
	if (pids[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(close(fd[0]), close(fd[1]));
		exec_tree(tree->left, env);
		exit(exit_code);
	}
	pids[1] = fork();
	if (pids[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(close(fd[0]), close(fd[1]));
		exec_tree(tree->right, env);
		exit(exit_code);
	}
	(close(fd[0]), close(fd[1]));
	(wait(NULL), wait(NULL));
}

void	exec_b_op(t_tree *tree, t_list *env)
{
	if (tree->n_type == N_OR)
	{
		exec_tree(tree->left, env);
		if (exit_code == 0)
			exec_tree(tree->right, env);
	}
	if (tree->n_type == N_AND)
	{
		exec_tree(tree->left, env);
		if (exit_code != 0)
			exec_tree(tree->right, env);
	}
}

void	exec_subprocces(t_tree **tree, t_list *env)
{
	pid_t	pid;

	if ((*tree)->subshell == true)
	{
		pid = fork();
		if (pid == 0)
		{
			(*tree)->subshell = false;
			exec_tree(*tree, env);
			exit(0);
		}
		waitpid(pid, NULL, 0);
	}
}

void	expand_cmds(t_cmd **cmd)//revisar punteros
{
	void	*tmp;

	tmp = (*cmd)->redirs;
	while ((*cmd)->redirs)
	{
		if ((*cmd)->redirs->redir_type != T_HEREDOC)
			(*cmd)->redirs->file->str = expand_vars((*cmd)->redirs->file->str
				, (*cmd)->env);
		(*cmd)->redirs = (*cmd)->redirs->next;
	}
	(*cmd)->redirs = tmp;
	tmp = (*cmd)->args;
	while ((*cmd)->args)
	{
		(*cmd)->args->str = expand_vars((*cmd)->args->str, (*cmd)->env);
		(*cmd)->args = (*cmd)->args->next;
	}
	(*cmd)->args = tmp;
}

//también necesito la raíz del árbol
void	exec_tree(t_tree *tree, t_list *env)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (tree->subshell == true)
	{
		exec_subprocces(&tree, env);
		return ;
	}
	if (tree->n_type == N_PIPE)
		exec_pipe(tree, env);
	exec_b_op(tree, env);
	if (tree->n_type == N_CMND)
	{
		expand_cmds(&tree->cmd);
		make_redirections(tree->cmd->redirs, env);
		tree->cmd->env = env;
		if (tree->cmd->is_builtin)
		{
			exit_code = run_built_in(tree->cmd);//necesitamos liberar el arbol con exit
			// dup2(fd_in, STDIN_FILENO);
			// dup2(fd_out, STDOUT_FILENO);
			// close(fd_in);
			// close(fd_out);
		}
		else
			exit_code = run_program(tree->cmd);
	}
}
