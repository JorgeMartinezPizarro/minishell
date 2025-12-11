/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:23:03 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/11 04:24:39 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

char	*iter_line(char *line);
int		valid_quotes(char *line);
int		which_operator(char *line);
void	print_tokens(t_token_list *tokens);
void	free_and_exit(t_token_list *tokens);

#endif