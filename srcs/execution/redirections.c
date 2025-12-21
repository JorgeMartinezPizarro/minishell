/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:48:20 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/21 21:18:29 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_jorge.h"

void	here_doc_aux(t_redir *redir, t_list *env, int *fd)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (redir->file->type != T_SINGLE_QUOTE)
			line = expand_vars(line, env);
		ft_putendl_fd(line, fd[1]);
		if (ft_strcmp(line, redir->file->str) == 0)
		{
			free(line);	
			break ;
		}
	}
	exit(0);
}

int	here_doc(t_redir *redir, t_list *env)
{
	int		fd[2];
	pid_t	pid;

	pid = fork();
	if (pid == -1 || pipe(fd) == -1)
		return (-1);
	if (pid == 0)
		here_doc_aux(redir, env, fd);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}

int	redir_files(t_redir *redir)
{
	int	fd;

	fd = 0;
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

int	make_redirections(t_redir *redirs, t_list *env)
{
	while (redirs)
	{
		if (redir_files(redirs) == -1)
			return (-1);
		if (redirs->redir_type == T_HEREDOC)
			if (here_doc(redirs, env) == -1)
				return (-1);
		redirs = redirs->next;
	}
	return (0);
}
