/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:50:01 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/20 13:50:36 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "structs.h"

void	exec_b_op(t_tree *tree, e_node_type type);
void	exec_subprocces(t_tree **tree);
void	exec_tree(t_tree *tree);
void	free_tree(t_tree *tree);
void	exec_pipe(t_tree *tree);

#endif