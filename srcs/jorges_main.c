#include "minishell_jorge.h"
#include "libft.h"
#include <unistd.h>

// Just a prototype on what to be run on every build in command.
// TODO: Merge with other main.c code.
int main(int argc, char **args, char **env)
{
	if (argc < 2)
	{
		char *line = get_next_line(1);
		while (line)
		{
			
			line = get_next_line(1);
		}
	}
	t_command com;
	//
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
	com.cwd = getcwd(NULL, 0);
	com.env = load_env_values(env);
	int exit_code = run_command(&com);

	free_env(&com.env);
	if (exit_code == 1)
		return 0;
	else
		return 1;
}