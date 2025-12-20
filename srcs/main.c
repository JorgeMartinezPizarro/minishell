/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:30:09 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/20 14:41:43 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
aquí en la función expand_tokens quiero que se expanda todo en vez de solo los *

Jorge tiene las dos funciones separadas y solo expande los strings tipo word
así que podría cambiar en el tokenizer que add_quotes pusiera el contenido dentro
de "" como tipo word
*/
int	exec_line(char *line, char **env)
{
	t_tokens	*tokens;
	t_tree		*tree;

	tokens = NULL;
	tree = NULL;
	if (!tokenize(line, &tokens))
		return ;
	expand_tokens(&tokens, get_cwd(NULL, 0));
	if(!make_tree(tokens, NULL))
	{
		free_tokens(tokens);
		return ;
	}
	free_tokens(tokens);
	exec_tree(tree);
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
