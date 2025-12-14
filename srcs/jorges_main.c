#include "minishell_jorge.h"
#include "libft.h"


// Just a prototype on what to be run on every build in command.
// TODO: Merge with other main.c code.

// Del readline se obtiene una estructura t_tree que tenemos que definir,
// cada rama tiene un puntero al entorno (ejemplo: un comando define A y el siguiente lo usa)
// run_tree recibe el arbol de comandos y segun el codigo de exit de cada uno, va al siguiente
// o termina.
// No tengo pensado como procesar los pipes, en verdad es una secuencia de t_commands, cada uno
// lleva el valor de retorno del anterior como ultimo parametro.

// Usaremos para manejar los comandos:

// 		readline, rl_clear_history, rl_on_new_line
//		rl_replace_line, rl_redisplay, add_history
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
		char *line = readline(">>> ");
		
		while (line)
		{
			char **words = ft_split(line, ' ');
			com.command = ft_strreplace(words[0], "\n", "");
			com.args = words;
			com.argc = strarr_len(words);
			int exit_code = run_command(&com);
			(void)exit_code;			
			line = readline(">>> ");
		}
		free_env(&com.env);
	}
	
	
}