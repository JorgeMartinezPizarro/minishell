#ifndef MINISHELL_H
# define MINISHELL_H

const char *LINE_BEGIN = "\033[1;32muser@MINISHELL-1:\033[0m ";

// A command can be a list of piped commands.

typedef struct s_command
{
	char	*name;
	char	**args;
	int		argc;
} t_command;

// Extend structure for system variables:
// - variables

void	parse_command(char *line);
#endif