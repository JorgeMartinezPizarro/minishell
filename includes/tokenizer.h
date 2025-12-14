/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:23:03 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/14 02:06:52 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

void	print_tokens(t_token_list *tokens);
bool	valid_quotes(char *line);
char	*iter_line(char *line);
int		which_operator(char *line);

#endif