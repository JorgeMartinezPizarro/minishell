/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:48:20 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/29 17:27:16 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_heredoc(t_shell *shell, int *fds, int p_fd, char *delimiter)
{
	free(delimiter);
	free_shell(shell);
	close(p_fd);
	close(fds[0]);
	close(fds[1]);
	exit(0);
}

static void	here_doc_aux(t_redir *redir, t_shell *shell, int *p_fd, int *fds)
{
	char	*delimiter;
	char	*line;

	delimiter = trim_quotes(ft_strdup(redir->file->str));
	close(p_fd[0]);
	setup_signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (ft_putendl_fd("warning: eof not expected", 2),
				free(delimiter), free_shell(shell), close(p_fd[1]),
				close(fds[0]), close(fds[1]), exit(1));
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (*redir->file->str != '\'')
			line = expand_vars(line, shell->env);
		ft_putendl_fd(line, p_fd[1]);
		free(line);
	}
	exit_heredoc(shell, fds, p_fd[1], delimiter);
}

static int	here_doc(t_redir *redir, t_shell *shell, int *fds)
{
	int		p_fd[2];
	int		status;
	pid_t	pid;

	if (pipe(p_fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(p_fd[0]), close(p_fd[1]),
			close(fds[0]), close(fds[1]), -1);
	if (pid == 0)
		here_doc_aux(redir, shell, p_fd, fds);
	close(p_fd[1]);
	setup_signals_parent_waiting();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(p_fd[0]);
		return (-1);
	}
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	return (0);
}

static int	redir_files(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->redir_type == T_REDIR_IN)
		fd = open(redir->file->str, O_RDONLY);
	else if (redir->redir_type == T_REDIR_TR)
		fd = open(redir->file->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->redir_type == T_APPEND)
		fd = open(redir->file->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), -1);
	if (redir->redir_type == T_APPEND || redir->redir_type == T_REDIR_TR)
		dup2(fd, STDOUT_FILENO);
	else if (redir->redir_type == T_REDIR_IN)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	make_redirections(t_redir *redirs, t_shell *shell, int *fds)
{
	while (redirs)
	{
		if (redirs->redir_type != T_HEREDOC)
			if (redir_files(redirs) == -1)
				return (-1);
		if (redirs->redir_type == T_HEREDOC)
			if (here_doc(redirs, shell, fds) == -1)
				return (-1);
		redirs = redirs->next;
	}
	return (0);
}
