/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:24:04 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/18 09:29:24 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

t_tokens	*division_point(t_tokens *start, t_tokens *end);
bool		is_redir(t_tokens *token);
void		iter_paren(t_tokens **tokens);
void		add_redir(t_redir **redirs, t_tokens **token);
void		assign_node_type(t_tree **node, t_tokens *token);
bool		everything_inside_paren(t_tokens *start, t_tokens *end);
void		remove_paren(t_tree **tree, t_tokens **start, t_tokens **end);

#endif