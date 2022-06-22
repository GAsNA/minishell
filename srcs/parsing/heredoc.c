/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:59 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 22:01:24 by rleseur          ###   ########.fr       */
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

static void	handle_signals_heredoc(void)
{
	signal(SIGINT, ctrl_c_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

static void	write_in_file(char *line, t_lenv *lenv, int fd)
{
	int		i;
	int		j;
	int		n;
	int		inte;
	char	*new_line;

	j = 0;
	while (there_are_expand(&line[j]))
	{
		inte = 0;
		i = -1;
		n = get_k_n(line, &i, &inte);
		if (n > 0 || inte)
		{
			new_line = make_expand(line, n, lenv, inte);
			free(line);
			line = new_line;
		}
		j = i;
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

static int	end_check(int fd, int fd2, char *line)
{
	free(line);
	close(fd);
	if (g_status == 42)
	{
		dup2(fd2, 0);
		close(fd2);
		return (0);
	}
	return (1);
}

int	make_heredoc(char *s, t_lenv *lenv)
{
	int		fd;
	int		fd2;
	char	*line;
	char	*file;

	file = "/tmp/.tmp.heredoc";
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	line = NULL;
	fd2 = dup(0);
	while (!line || ft_strcmp(line, s) != 0)
	{
		handle_signals_heredoc();
		line = readline(">");
		if (g_status == 42)
			break ;
		//if (!line[0])
		//	continue ;
		if (line && ft_strcmp(line, s) != 0)
		{
			write_in_file(line, lenv, fd);
			line = NULL;
		}
	}
	if (!end_check(fd, fd2, line))
		return (-1);
	return (open(file, O_RDWR, 0666));
}
