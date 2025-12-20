/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:24:04 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/20 13:50:50 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "tokenizer.h"

t_tokens	*division_point(t_tokens *start, t_tokens *end);
t_tree		*make_tree(t_tokens *start, t_tokens *end);
void		free_cmnd(t_cmd *cmd);
bool		is_redir(t_tokens *token);
void		iter_paren(t_tokens **tokens);
void		add_redir(t_redir **redirs, t_tokens **token);
void		assign_node_type(t_tree **node, t_tokens *token);
bool		everything_inside_paren(t_tokens *start, t_tokens *end);
void		remove_paren(t_tree **tree, t_tokens **start, t_tokens **end);

#endif