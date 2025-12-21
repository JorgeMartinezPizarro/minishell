/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 21:48:20 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/21 14:12:13 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_jorge.h"

/*
escribir en un pipe y gestionar señales
*/
int	here_doc(t_redir *redir, t_list *env)
{
	char	*line;
	pid_t	pid;
	int		fd[2];

	pid = fork();
	if (pid == -1 || pipe(fd) == -1)
		return (-1);
	if (pid == 0)
	{
		dup2(STDOUT_FILENO, fd[1]);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (redir->file->type != T_SINGLE_QUOTE)
				line = expand_vars(line, env);
			write(STDIN_FILENO, line, ft_strlen(line));
			if (ft_strcmp(line, redir->file->str) == 0)
				break ;
		}
	}
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
		dup2(STDOUT_FILENO, fd);
	else if (redir->redir_type == T_REDIR_IN)
		dup2(STDIN_FILENO, fd);
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
