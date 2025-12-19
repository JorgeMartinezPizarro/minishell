#include "minishell.h"
#include "libft.h"
#include "minishell_jorge.h"

// Just a prototype on what to be run on every build in command.
// TODO: Merge with other main.c code.

// Del readline se obtiene una estructura t_tree que tenemos que definir,
// cada rama tiene un puntero al entorno (ejemplo: un comando define A y el siguiente lo usa)
// run_tree recibe el arbol de comandos y segun el codigo de exit de cada uno, va al siguiente
// o termina.
// No tengo pensado como procesar los pipes, en verdad es una secuencia de t_cmds, cada uno
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

int	exec_line(t_cmd *com, char *line)
{
	//t_tree		*tree;
	//tree = NULL;
	if (!tokenize(line, &com->args))
		return 1;
	t_tokens *expanded;

	expanded = expand_tokens(com->args, com->cwd);
	free_tokens(com->args);
	com->args = expanded; 
	// TODO: Cambiar por execute_tree cuando funcione.
	//tree = make_tree(com->args, NULL);
	//tree->cmd = com;
	//execute_tree(tree);
	if (is_built_in(com))
		run_built_in(com);
	else
		run_program(com);
	if (com->args)
		free_tokens(com->args);
	com->args = NULL;
	add_history(line);
	return 1;
}

char	*get_name(t_list *env)
{
	// TODO: free 
	
	char *var = get_env_value(env, "SESSION_MANAGER");

	char **vals = ft_split(var, ':');

	char **its = ft_split(vals[0], '.');

	char **els = ft_split(its[0], '/');

	char *sol = ft_strdup(els[1]);

	free_str_array(vals);
	free_str_array(its);
	free_str_array(els);
	
	return sol;
}

int main(int argc, char **args, char **env)
{
	t_cmd com;

	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
	com.cwd = getcwd(NULL, 0);
	com.env = load_env_values(env);
	com.args = NULL;

	if (argc > 2 && ft_strcmp(args[1], "-c") == 0)
	{
		exec_line(&com, args[2]);
	}
	else if (argc < 2)
	{
		char *str = ft_strdup("\033[1;35m${USER}@#### >>> \033[0m");
		char *head = expand_vars(str, com.env);
		char *name = get_name(com.env);
		char *tmp = head;
		head = ft_strreplace(tmp, "####", name);
		free(tmp);
		free(name);
		char *line = readline(head);
		
		while (line)
		{
			exec_line(&com, line);
			line = readline(head);
		}
		free(head);
		
	}
	else {
		ft_printf("Usage %s -c <command>\n", args[0]);
		return 1;
	}
	free_env(&com.env);
	free(com.cwd);
	
	return 0;
}
