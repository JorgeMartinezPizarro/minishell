/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:41:48 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 19:40:44 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "minishell.h"

static void	exec_b_op(t_tree *node, t_shell *shell)
{
	if (node->n_type == N_OR)
	{
		exec_tree(node->left, shell);
		if (g_exit_code != 0)
			exec_tree(node->right, shell);
	}
	if (node->n_type == N_AND)
	{
		exec_tree(node->left, shell);
		if (g_exit_code == 0)
			exec_tree(node->right, shell);
	}
}

static void	exec_subprocces(t_tree **node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	if ((*node)->subshell == false)
		return ;
	(*node)->subshell = false;
	pid = fork();
	if (pid == -1)
		return (free_shell(shell), exit(1));
	if (pid == 0)
	{
		shell->is_child = true;
		exec_tree(*node, shell);
		free_shell(shell);
		exit(g_exit_code);
	}
	waitpid(pid, &status, 0);
	g_exit_code = WEXITSTATUS(status);
}

static void	expand_cmds(t_tokens **args, t_redir *redirs, t_shell *shell)
{
	t_tokens	*tmp_args;
	t_redir		*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->redir_type != T_HEREDOC)
		{
			tmp->file->str = expand_vars(tmp->file->str, shell->env);
			tmp->file->str = trim_quotes(tmp->file->str);
		}
		tmp = tmp->next;
	}
	expand_env_tokens(args, shell->env);
	expand_wildcard_tokens(args, get_env_value(shell->env, "PWD"));
	tmp_args = *args;
	while (tmp_args)
	{
		tmp_args->str = trim_quotes(tmp_args->str);
		tmp_args = tmp_args->next;
	}
}

static void	exec_commands(t_tree *node, t_shell *shell)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	expand_cmds(&node->cmd->args, node->cmd->redirs, shell);
	if (make_redirections(node->cmd->redirs, shell->env) == -1)
		return (free_shell(shell), exit(1));
	node->cmd->env = shell->env;
	if (node->cmd->is_builtin)
		g_exit_code = run_built_in(node->cmd, shell);
	else
		g_exit_code = run_program(node->cmd, shell);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

void	exec_tree(t_tree *node, t_shell *shell)
{
	if (node->subshell == true)
		return (exec_subprocces(&node, shell), (void)0);
	if (node->n_type == N_PIPE)
		exec_pipe(node, &shell);
	exec_b_op(node, shell);
	if (node->n_type == N_CMND)
		exec_commands(node, shell);
}
