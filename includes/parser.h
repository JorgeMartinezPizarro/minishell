/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:24:04 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/13 03:10:33 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

void	set_b_op(t_tree **tree, t_token_list *token);
bool	b_op_after_paren(t_token_list *tokens);
void	iter_paren(t_token_list **tokens);

#endif