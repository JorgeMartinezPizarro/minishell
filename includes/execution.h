/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:50:01 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/20 22:36:55 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "structs.h"

void	exec_subprocces(t_tree **tree, t_list *env);
void	exec_tree(t_tree *tree, t_list *env);
void	exec_b_op(t_tree *tree, t_list *env);
void	exec_pipe(t_tree *tree, t_list *env);
void	make_redirections(t_redir *redirs);
int		redir_files(t_redir *redir);
int		here_doc(t_redir *redir);
void	free_tree(t_tree *tree);

#endif