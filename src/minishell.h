#ifndef MINISHELL_H
# define MINISHELL_H

// A command can be a list of piped commands.
typedef struct s_command
{
	char	*name;
	char	**args;
	int		argc;
} t_command;
// Extend structure for system variables:
// - variables

#endif