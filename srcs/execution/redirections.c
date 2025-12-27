/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:48:20 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/26 22:47:39 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_aux(t_redir *redir, t_list *env, int *fd)
{
	char	*delimiter;
	char	*line;

	delimiter = trim_quotes(ft_strdup(redir->file->str));
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (*redir->file->str != '\'')
			line = expand_vars(line, env);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	free(delimiter);
	close(fd[1]);
	exit(0);
}

static int	here_doc(t_redir *redir, t_list *env)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (close(fd[0]), close(fd[1]), -1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
		here_doc_aux(redir, env, fd);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
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
		return (perror("open error:"), -1);
	if (redir->redir_type == T_APPEND || redir->redir_type == T_REDIR_TR)
		dup2(fd, STDOUT_FILENO);
	else if (redir->redir_type == T_REDIR_IN)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	make_redirections(t_redir *redirs, t_list *env)
{
	while (redirs)
	{
		if (redirs->redir_type != T_HEREDOC)
			if (redir_files(redirs) == -1)
				return (-1);
		if (redirs->redir_type == T_HEREDOC)
			if (here_doc(redirs, env) == -1)
				return (-1);
		redirs = redirs->next;
	}
	return (0);
}
