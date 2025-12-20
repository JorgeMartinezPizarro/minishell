/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:23:03 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/20 13:51:09 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "structs.h"

void	add_token_to_list(t_tokens **tokens, char *str, int type);
int		tokenize(char *line, t_tokens **tokens);
void	print_tokens(t_tokens *tokens);
void	free_tokens(t_tokens *tokens);
int		which_operator(char *line);
bool	valid_quotes(char *line);
bool	valid_paren(char *line);
char	*iter_line(char *line);

#endif