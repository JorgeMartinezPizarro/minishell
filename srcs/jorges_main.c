#include "minishell_jorge.h"
#include "libft.h"
#include <unistd.h>

// Just a prototype on what to be run on every build in command.
// TODO: Merge with other main.c code.
int main(int argc, char **args, char **env)
{
	t_command com;
	com.cwd = getcwd(NULL, 0);
	com.env = load_env_values(env);

	if (argc > 1)
	{
		char **words = ft_split(args[1], ' ');
		com.command = words[0];
		com.args = words;
		com.argc = strarr_len(words);
		int exit_code = run_command(&com);
		free_env(&com.env);
		if (exit_code == 1)
			return 0;
		else
			return 1;
	}
	else if (argc < 2)
	{
		write(1, ">> ", 3);
		char *line = get_next_line(0);
		
		while (line)
		{
			char **words = ft_split(line, ' ');
			com.command = ft_strreplace(words[0], "\n", "");
			com.args = words;
			com.argc = strarr_len(words);
			int exit_code = run_command(&com);
			(void)exit_code;			
			write(1, ">> ", 3);
			line = get_next_line(0);
		}
		free_env(&com.env);
	}
	
	
}