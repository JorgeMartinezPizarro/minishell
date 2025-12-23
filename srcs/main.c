#include "minishell.h"
#include "libft.h"
#include "minishell_jorge.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>

int	exit_code = 0;

int	exec_line(t_shell *shell, char *line)
{
	t_tokens	*tokens;

	tokens = NULL;
	if (!tokenize(line, &tokens))
		return 1;
	if (!tokens)
		return 1;
	shell->first_node = make_tree(tokens, NULL);
	if (!shell->first_node)
		  return (syntax_error(), 1);
	exec_tree(shell->first_node, shell);
	free_tree(shell->first_node);
	free_tokens(tokens);
	add_history(line);
	return 1;
}


// TODO: split one task to each function.
int main(int argc, char **args, char **env)
{
	t_shell	*shell;

	exit_code = 0;
	setup_signals_interactive();
	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
	{//se puede hacer una función que haga esto ya que se hace tanto
		exit_code = 1;
		perror("malloc");
		return (1);
	}
	shell->env = load_env_values(env);
	if (argc > 2 && ft_strcmp(args[1], "-c") == 0)
		exec_line(shell, args[2]);
	else if (argc < 2)
	{
		char *str = ft_strdup("\033[1;35m${USER}@#### >>> \033[0m");
		char *head = expand_vars(str, shell->env);
		char *name = get_prompt(shell->env);
		char *tmp = head;
		head = ft_strreplace(tmp, "####", name);
		free(tmp);
		free(name);
		char *line = readline(head);
		while (line)
		{
			exec_line(shell, line);
			free(line);
			line = readline(head);
		}
		free(head);
	}
	else
	{
		ft_printf("Usage %s -c <command>\n", args[0]);
		free_env(&shell->env);
		free(shell);
		return (1);
	}
	free_env(&shell->env);
	free(shell);
	return (0);
}
