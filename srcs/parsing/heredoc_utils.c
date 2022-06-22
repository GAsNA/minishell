/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:01:40 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/22 18:56:25 by rleseur          ###   ########.fr       */
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

int	end_check(int fd, int fd2)
{
	close(fd);
	if (g_status == 42)
	{
		dup2(fd2, 0);
		close(fd2);
		return (0);
	}
	close(fd2);
	return (1);
}

int	check(char *line)
{
	if (g_status == 42)
		return (0);
	if (!line)
	{
		printf("\n");
		return (0);
	}
	return (1);
}

void	check_quotes(char *s, int *expand)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\'' || s[i] == '"')
			*expand = 0;
}
