#include "minishell.h"
#include "libft.h"
#include "minishell_jorge.h"

// TODO: usar variable global aqui.
int	exit_code = 0;

void sigint_handler(int sign)
{
    // TODO: mirar bien el shell level y el isatty para ver que shell debe reaccionar
	
	(void)sign;
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
	char *var = get_env_value(env, "SESSION_MANAGER");
	if (!var)
		return ft_strdup("unknown");
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
		char *line = readline(head);
		
		while (line)
		{
			if (ft_strcmp(line, "") != 0)//si getline siempre devuelve nl sería in
				exec_line(env_lst, line);
			line = readline(head);
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
