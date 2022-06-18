/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:59 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/18 15:05:47 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_n(char *line)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (line[++i])
	{
		if ((line[i] == '$' && line[i + 1] != '?' && n == 0) || n > 0)
		{
			if ((!line[i] || line[i] == ' ' || line[i] == '\'' || line[i] == '"') && n > 0)
				break ;
			n++;
		}
	}
	return (n - 1);
}

int	make_heredoc(char *s, t_lenv *lenv)
{
	int		fd;
	int		n;
	char	*line;
	char	*new_line;
	char	*file;

	file = "/tmp/.tmp.heredoc";
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	line = NULL;
	while (!line || ft_strcmp(line, s) != 0)
	{
		line = readline(">");
		if (line && ft_strcmp(line, s) != 0)
		{
			n = get_n(line);
			if (n > 0)
			{
				new_line = make_expand(line, n, lenv);
				free(line);
				line = new_line;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
			line = NULL;
		}
	}
	free(line);
	close(fd);
	fd = open(file, O_RDWR, 0666);
	return (fd);
}
