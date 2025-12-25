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
	int			i;

	// ignorar líneas vacías o solo espacios/tabs
	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return 1;

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

	if (isatty(STDIN_FILENO))
		add_history(line);

	return 1;
}

static void	shell_loop(t_shell *shell)
{
	if (!isatty(STDIN_FILENO))
	{
		char	*line;
		int		first_line;

		first_line = 1;
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (first_line && line[0] == '#' && line[1] == '!')
			{
				first_line = 0;
				free(line);
				line = get_next_line(STDIN_FILENO);
				continue;
			}
			first_line = 0;
			exec_line(shell, line);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		return ;
	}
	char *head = get_prompt(shell->env);
	char *line = readline(head);
	while (line)
	{
		exec_line(shell, line);
		free(line);
		head = get_prompt(shell->env);
		line = readline(head);
	}
	free(head);
}

void	malloc_failed()
{
	exit_code = 1;
	perror("malloc");
}

void	update_minishell_level(t_list **env)
{
	char *str;
	char *nbr;
	int i;

	str = get_env_value(*env, "MSHLVL");
	if (!str)
		nbr = ft_strdup("1");
	else
	{
		i = ft_atoi(str) + 1;
		nbr = ft_itoa(i);
	}
	set_env_value(env, "MSHLVL", nbr);
	free(nbr);
}

void init_required_env(t_list **env)
{
	char *str = getcwd(NULL, 0);
	if (!get_env_value(*env, "PWD"))
		set_env_value(env, "PWD", str);
	if (!get_env_value(*env, "OLDPWD"))
		set_env_value(env, "OLDPWD", str);
	free(str);
}

int main(int argc, char **args, char **env)
{
	t_shell	*shell;

	setup_signals_interactive();
	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (malloc_failed(), 1);
	shell->env = load_env_values(env);
	init_required_env(&shell->env);
	update_minishell_level(&shell->env);
	if (ft_atoi(get_env_value(shell->env, "MSHLVL")) > MAX_MINISHELL_LEVEL)
		return (ft_printf("error: minishell refused to open.\n"), 1);
	if (argc > 2 && ft_strcmp(args[1], "-c") == 0)
		exec_line(shell, args[2]);
	else if (argc == 2)
	{
		int fd;

		fd = open(args[1], O_RDONLY);
		if (fd < 0)
		{
			perror(args[1]);
			exit_code = 1;
		}
		else
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
			shell_loop(shell);
		}
	}
	else
		shell_loop(shell);
	free_env(&shell->env);
	free(shell);
	return (exit_code);
}
