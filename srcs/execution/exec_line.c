/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:03:10 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 17:03:15 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

int	exec_line(t_shell *shell, char *line)
{
	t_tokens	*tokens;
	int			i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (1);
	tokens = NULL;
	if (!tokenize(line, &tokens) || !tokens)
		return (1);
	shell->first_node = make_tree(tokens, NULL);
	if (!shell->first_node)
		return (write(2, "Syntax error\n", 13), 1);
	exec_tree(shell->first_node, shell);
	free_tokens(tokens);
	free_tree(shell->first_node);
	if (isatty(STDIN_FILENO))
		add_history(line);
	return (1);
}
