/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:31:40 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/29 17:32:54 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_heredoc(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	exit(130);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
