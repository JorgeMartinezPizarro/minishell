#include "minishell.h"
#include "libft.h"
#include "minishell_jorge.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>

int	exit_code = 0;

static int	exec_line(t_shell *shell, char *line)
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
	free_tokens(tokens);
	free_tree(shell->first_node);
	add_history(line);
	return 1;
}

static void	shell_loop(t_shell *shell)
{
	if (!isatty(STDIN_FILENO))
	{
		char *line = get_next_line(STDIN_FILENO);
		while (line)
		{
			exec_line(shell, line);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		return ;
	}
	char *head = get_prompt(shell->env);
	// TODO: if is not interactive, read from stdin_fileno
	
	char *line = readline(head);
	while (line)
	{
		exec_line(shell, line);
		free(line);
		line = readline(head);
	}
	free(head);
}

// TODO: mover esto a utils?
void	malloc_failed()
{
	exit_code = 1;
	perror("malloc");
}

void	update_minishell_level(t_list **env)
{
	char *str = get_env_value(*env, "MSHLVL");
	char *nbr;
	if (!str)
		nbr = ft_strdup("1");
	else{
		int i = ft_atoi(str) + 1;
		nbr = ft_itoa(i);
	}
	set_env_value(env, "MSHLVL", nbr);
	free(nbr);
}

// Vamos a usar una variable propia
// MSHLVL para contar cuantas shells llevamos abiertas.
int main(int argc, char **args, char **env)
{
	t_shell	*shell;

	setup_signals_interactive();
	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (malloc_failed(), 1);
	shell->env = load_env_values(env);
	update_minishell_level(&shell->env);
	if (ft_atoi(get_env_value(shell->env, "MSHLVL")) > MAX_MINISHELL_LEVEL)
		return (ft_printf("error: minishell refused to open.\n"), 1);
	if (argc > 2 && ft_strcmp(args[1], "-c") == 0)
		exec_line(shell, args[2]);
	else if (argc < 2)
		shell_loop(shell);
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
