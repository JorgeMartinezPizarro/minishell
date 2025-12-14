/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:30:09 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/14 04:44:11 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution(t_tree *tree)
{
	//expandir variables durante la ejecución justo antes de ejecutar el comando

	//gestionar los errores y los códigos de salida durante la ejecución
}

int	exec_line(char *line, char **env)
{
	t_token_list	*tokens;
	t_tree			*tree;

	tokens = NULL;
	tree = NULL;
	if (!tokenize(line, &tokens))
		return ;
	make_tree(&tree, tokens);
	//free_tokens();
	execution(tree);
}

int	main(int ac, char **av, char **envp)
{
	char	**env;
	char	*line;
	char	*user;

/*
	mirar como gestiona bash env porque hay casos en los
	que necesita dos variables de entorno al hacer exports y
	en algunos casos de fallo
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
