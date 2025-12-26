/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:45:03 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 18:13:59 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "minishell_jorge.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	g_exit_code = 0;

static void	shell_loop_noninteractive(t_shell *shell)
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
			continue ;
		}
		first_line = 0;
		exec_line(shell, line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

static void	exec_input(t_shell *shell, char *line)
{
	char	**lines;
	int		i;

	lines = ft_split(line, '\n');
	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		exec_line(shell, lines[i]);
		i++;
	}
	free_str_array(lines);
}

static void	shell_loop(t_shell *shell)
{
	char	*head;
	char	*line;

	if (!isatty(STDIN_FILENO))
		return (shell_loop_noninteractive(shell));
	head = get_prompt(shell->env);
	line = readline(head);
	while (line)
	{
		exec_input(shell, line);
		free(line);
		free(head);
		head = get_prompt(shell->env);
		line = readline(head);
	}
	free(head);
}

static void	handle_input(int argc, char **args, t_shell *shell)
{
	int	fd;

	if (argc > 2 && ft_strcmp(args[1], "-c") == 0)
		exec_line(shell, args[2]);
	else if (argc == 2)
	{
		fd = open(args[1], O_RDONLY);
		if (fd < 0)
		{
			close(fd);
			perror(args[1]);
			g_exit_code = 1;
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
}

int	main(int argc, char **args, char **env)
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
	handle_input(argc, args, shell);
	free_env(&shell->env);
	free(shell);
	return (g_exit_code);
}
