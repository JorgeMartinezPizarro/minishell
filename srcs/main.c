/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:30:09 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/18 16:39:40 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_line(char *line, char **env)
{
	t_tokens	*tokens;
	t_tree		*tree;

	tokens = NULL;
	tree = NULL;
	if (!tokenize(line, &tokens))
		return ;
	if(!make_tree(tokens, NULL))
	{
		free_tokens(tokens);
		return ;
	}
	free_tokens(tokens);
	execute_tree(tree);
	free_tree(tree);
}

int	main(int ac, char **av, char **envp)
{
	char	**env;
	char	*line;
	char	*user;

/*
gestionar cuando te pasan un comando que borre la variable de entorno
y luego ./minishell y también los shell_lvl
*/
	env = getenv(envp);
	user = expand_user();
	if (ft_strncmp(av[1], "-c", 3))
		exec_line(av[2], env);
	while (1)
	{
		line = readline(user);
		exec_line(line, env);
	}
	return (0);
}
