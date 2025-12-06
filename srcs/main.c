/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:30:09 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/06 20:05:19 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse(t_parsed_line *parsed_line, t_token_list tokens)
{
	//detectar errores sintácticos

	//construir la estructura que usará el executor

	//agrupar los tokens

	//ejecutar todo redireccionando la información

	//gestionar los errores y los códigos de salida durante la ejecución
}

void	execution(t_parsed_line parsed_line)
{
	//ejecutar los comandos en orden como el pipex pero redireccionando

	//expandir variables durante la ejecución justo antes de ejecutar el comando

	//
}

int	exec_line(char *line)
{
	t_token_list	tokens;
	t_parsed_line	parsed_line;

	if (!tokenize(line, &tokens))
		return ;
	if (!parse(&parsed_line, tokens))
		return ;//si tokenize o parse devuelve 0 saltar ejecución
	execution(parsed_line);
}

int	main(int ac, char **av)
{
	char	**env;
	char	*line;
	char	*user;

	/*obtener la variable de entorno
	mirar como lo gestiona bash porque hay casos en los
	que necesita dos variables de entorno al hacer exports y
	en algunos casos de fallo

	además hacer funciones para usar la variable de entorno
	*/
	env = getenv();
	//sacar el valor de $USER para imprimirlo en pantalla
	user = get_user();
	if (ft_strncmp(av[1], "-c", 3))
		exec_line(av[2]);
	while (1)
	{
		line = readline(user);
		exec_line(line);
	}
	return (0);
}
