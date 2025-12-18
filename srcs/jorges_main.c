#include "minishell.h"
#include "libft.h"
#include "minishell_jorge.h"

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

void sigint_handler(int signo)
{
    (void)signo;                // ignorar el argumento
    write(1, "\n", 1);          // imprime la nueva línea
    rl_replace_line("", 0);     // borra la línea que se estaba escribiendo
    rl_on_new_line();            // indica a readline que estamos en una nueva línea
    rl_redisplay();              // redibuja prompt vacío
}

/*

int exec_tree(t_tree *tree)
{
	// Recorremos el arbol y devolvemos el int resultante.
}


*/

int	exec_line(t_command *com, char *line)
{
	// TODO: make_tree does not yet compile.
	//t_tree		*tree;
	// Aqui podemos ejecutar cada comando del arbol en vez 
	// de un solo comando.
	//tree = NULL;
	com->tokens = NULL;
	// TODO: Usar expand_wildcard in tokenize
	if (!tokenize(line, &com->tokens))
		return 1;
	com->tokens = expand_tokens(com->tokens, com->cwd);
	//tree = make_tree(com->tokens, NULL);
	//(void)tree;
	com->command = com->tokens->str;
	com->args = com->tokens->next;
	
	// TODO: move to exec_tree
	// El arbol tree tiene que recibir el comando
	// completo, que contiene los tokens, el env y cwd.
	// Podemos distinguir el tipo de comando
	if (is_built_in(com))
		com->exit_code = run_command(com);
	else
		com->exit_code = run_program(com);
	add_history(line);

	return com->exit_code;
}

// TODO: Por cada linea debemos aqui crear un arbol binario de comandos, y sobre ese 
// arbol iniciamos iterativamente comandos.
// Si los comandos son entre parentesis, se crea un clone de env nuevo para ese proceso, 
// para que no interfiera con el padre.
// En general la parte de crear el comando debe separarse en un fichero propio,
// y llamarse tantas veces como comandos contenta la linea 
// que recibimos.
int main(int argc, char **args, char **env)
{
	t_command com;

	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);

	com.cwd = getcwd(NULL, 0);
	com.env = load_env_values(env);

	if (argc > 2 && ft_strcmp(args[1], "-c") == 0)
	{
		exec_line(&com, args[2]);
	}
	else if (argc < 2)
	{
		char *str = ft_strdup("\033[1;32m${USER}@${NAME} >>> \033[0m");
		char *head = expand_vars(str, com.env);
		char *line = readline(head);
		
		while (line)
		{
			exec_line(&com, line);
			line = readline(head);
		}
		free_env(&com.env);
	}
	else {
		ft_printf("Usage %s -c <command>\n", args[0]);
		return 1;
	}
	return 0;
}