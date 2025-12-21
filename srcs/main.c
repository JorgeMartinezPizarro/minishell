/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:30:09 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/20 23:09:32 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_jorge.h"

int	exit_code = 0;

int	exec_line(char *line, t_list *env)
{
	t_tokens	*tokens;
	t_tree		*tree;

	tokens = NULL;
	tree = NULL;
	if (!tokenize(line, &tokens))
		return ;
	expand_tokens(&tokens, get_cwd(NULL, 0));
	tree = make_tree(tokens, NULL);
	free_tokens(tokens);
	if (!tree)
		return (syntax_error(), 1);
	exec_tree(tree, env);
	free_tree(tree);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env;
	char	*line;
	char	*user;

/*
gestionar cuando te pasan un comando que borre la variable de entorno
en tal caso creo que hay que construir el entorno

y luego ./minishell y también los shell_lvl
*/
	env = load_env_values(envp);
	if (ft_strncmp(av[1], "-c", 3))
		exec_line(av[2], env);
	while (1)
	{
		line = readline(user);
		if (exec_line(line, env) == 1)
		{
			exit_code = 1;
			break ;
		}
	}
	return (0);
}
