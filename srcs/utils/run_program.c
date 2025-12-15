#include "minishell_jorge.h"

int run_program(t_command *com)
{
	ft_printf("Running program %s\n", com->command);
	// TODO:
	// Search for runnables within PATH
	// Look if runnable
	// Run with execve
	return 1;
}