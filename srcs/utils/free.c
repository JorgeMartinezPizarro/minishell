/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:41:48 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/22 14:43:15 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"
#include "minishell.h"
#include "libft.h"

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens;
		free(tokens->str);
		tokens = tokens->next;
		free(tmp);
	}
}

void	free_cmnd(t_cmd *cmd)
{
	t_redir	*tmp;

	if (cmd->args)
		free_tokens(cmd->args);
	while (cmd->redirs)
	{
		tmp = cmd->redirs;
		if (cmd->redirs->file)
			free_tokens(cmd->redirs->file);
		cmd->redirs = cmd->redirs->next;
		free(tmp);
	}
	free(cmd);
}

void	free_tree(t_tree *tree)
{
	if (tree->n_type == N_CMND)
		free_cmnd(tree->cmd);
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free(tree);
}

void free_variable(void *content)
{
	t_variable *v = (t_variable *)content;
	free(v->name);
	free(v->value);
	free(v);
}

void free_env(t_list **vars)
{
	ft_lstclear(vars, free_variable);
}