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

void	exec_b_op(t_tree *node, t_shell *shell)
{
	if (node->n_type == N_OR)
	{
		exec_tree(node->left, shell);
		if (exit_code == 0)
			exec_tree(node->right, shell);
	}
	if (node->n_type == N_AND)
	{
		exec_tree(node->left, shell);
		if (exit_code != 0)
			exec_tree(node->right, shell);
	}
}

void	exec_subprocces(t_tree **node, t_shell *shell)
{
	pid_t	pid;

	if ((*node)->subshell == false)
		return ;
	pid = fork();
	if (pid == 0)
	{
		(*node)->subshell = false;
		exec_tree(*node, shell);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	expand_cmds(t_tokens **args, t_redir *redirs, t_list *env)
{
	while (redirs)
	{
		if (redirs->redir_type != T_HEREDOC)
			redirs->file->str = expand_vars(redirs->file->str, env);
		redirs = redirs->next;
	}
	expand_tokens(args, get_env_value(env, "PWD"));
	expand_env_tokens(args, env);
}

void	exec_tree(t_tree *node, t_shell *shell)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	exec_subprocces(&node, shell);
	if (node->n_type == N_PIPE)
		exec_pipe(node, shell);
	exec_b_op(node, shell);
	if (node->n_type == N_CMND)
	{
		expand_cmds(&node->cmd->args, node->cmd->redirs, shell->env);
		make_redirections(node->cmd->redirs, shell->env);
		node->cmd->env = shell->env;
		if (node->cmd->is_builtin)
			exit_code = run_built_in(node->cmd);
		else
			exit_code = run_program(node->cmd, shell);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
	}
	(void)fd_in;
	(void)fd_out;
}
