/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:01:40 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/22 11:03:07 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	ctrl_c_heredoc(int signum)
{
	(void)signum;
	close(0);
	printf("\n");
	g_status = 42;
}

void	handle_signals_heredoc(void)
{
	signal(SIGINT, ctrl_c_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
