/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:50:01 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/25 21:25:51 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "structs.h"

int		make_redirections(t_redir *redirs, t_list *env);
void	exec_tree(t_tree *tree, t_shell *shell);
void	exec_pipe(t_tree *tree, t_shell **shell);
void	free_shell(t_shell *shell);
void	free_tree(t_tree *tree);

#endif