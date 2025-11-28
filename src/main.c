/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:23:03 by jomarti3          #+#    #+#             */
/*   Updated: 2025/11/28 01:04:44 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

const char *line_begin = "\033[1;32muser@MINISHELL-1:\033[0m: ";

int	main(void)
{
	char	*line;
	t_command command;
	ft_printf(line_begin);
	line = get_next_line(1);
	while (line)
	{
		if (line[0] != '\n')
		{
			line[ft_strlen(line) - 1] = '\0';
			char **strings = ft_split(line, ' ');
			command.name = strings[0];
			// TODO: Filter command by name here
			ft_printf("Command '%s' not found\n", command.name);
		}
		free(line);
		ft_printf(line_begin);
		line = get_next_line(1);
	}
	free(line);
	return (0);
}