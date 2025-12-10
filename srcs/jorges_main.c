#include "minishell_jorge.h"
#include "libft.h"

// Just a prototype on what to be run on every build in command.
int main(int argc, char **args, char **env)
{
	(void)argc;
	t_command com;
	// TODO: First trivial version, isspace and more have to be taken into consideration here!
	char **words = ft_split(args[1], ' ');
	com.command = words[0];
	com.args = words;
	int c = 0;
	char **tmp = words;
	while (*tmp != NULL)
	{
		c++;
		tmp++;
	}	
	com.argc = c;
	com.env = env;
	int exit_code = run_command(&com);

	if (exit_code == 1)
		return 0;
	else
		return 1;
}