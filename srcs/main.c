#include "../includes/minishell.h"

int	parse(t_parsed_line *parsed_line, t_tokens_line tokenized_line)
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
	t_tokens_line	tokenized_line;
	t_parsed_line	parsed_line;

	if (!tokenize(line, &tokenized_line))
		return ;
	if (!parse(&parsed_line, tokenized_line))
		return ;//si tokenize o parse devuelve 0 saltar ejecución
	execution(parsed_line);
}

int	main(int ac, char **av)
{
	char	**env;
	char	*line;
	char	*user;

	//obtener la variable de entorno
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

int	valid_quotes(char *line)
{
	while (*line)
	{
		if (*line == '\"')
			line = ft_strchr(++line, '\"');
		else if (*line == '\'')
			line = ft_strchr(++line, '\'');
		if (!line)
			return (0);
		line++;
	}
	return (1);
}
