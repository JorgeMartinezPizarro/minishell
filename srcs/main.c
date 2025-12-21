#include "minishell.h"
#include "libft.h"
#include "minishell_jorge.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>

// exec_tree se comunica directamente con el main, no es 
// necesario usar una señal para eso. Otra opcion es 
// pasar la funcion de exit y clean por parametro.
int	exit_code = 0;

// Variable para identificar la minishell activa, para 
// reaccionar a control + c como lo hace shell.
volatile sig_atomic_t g_state = 0;

void sigint_handler(int sign)
{
    (void)sign;
	if (g_state != 1)
        return ;	
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

int	exec_line(t_list *env, char *line)
{
	t_tokens	*tokens;
	t_tree		*tree;

	tokens = NULL;
	if (!tokenize(line, &tokens))
		return 1;
	tree = make_tree(tokens, NULL);
	if (!tree)
		  return (syntax_error(), 1);
	exec_tree(tree, env);
	free_tree(tree);
	add_history(line);
	return 1;
}

char	*get_name(t_list *env)
{
	char **vals;
	char **its;
	char **els;
	char *sol;
	char *var;

	var = get_env_value(env, "SESSION_MANAGER");
	if (!var)
		return (ft_strdup("unknown"));
	vals = ft_split(var, ':');
	its = ft_split(vals[0], '.');
	els = ft_split(its[0], '/');
	sol = ft_strdup(els[1]);
	free_str_array(vals);
	free_str_array(its);
	free_str_array(els);
	return (sol);
}

int main(int argc, char **args, char **env)
{
	t_list	*env_lst;

	exit_code = 0;
	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
	env_lst = load_env_values(env);

	if (argc > 2 && ft_strcmp(args[1], "-c") == 0)
		exec_line(env_lst, args[2]);
	else if (argc < 2)
	{
		char *str = ft_strdup("\033[1;35m${USER}@#### >>> \033[0m");
		char *head = expand_vars(str, env_lst);
		char *name = get_name(env_lst);
		char *tmp = head;
		head = ft_strreplace(tmp, "####", name);
		free(tmp);
		free(name);
		g_state = 1;
		char *line = readline(head);
		g_state = 0;
		while (line)
		{
			g_state = 2;
			if (ft_strcmp(line, "") != 0) // Ignoramos lineas vacias.
				exec_line(env_lst, line);
			g_state = 0;
			g_state = 1;
			line = readline(head);
			g_state = 0;

		}
		free(head);
	}
	else
	{
		ft_printf("Usage %s -c <command>\n", args[0]);
		return (1);
	}
	return (0);
}
