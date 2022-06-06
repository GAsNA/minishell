/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:59 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/06 15:23:05 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_heredoc(char *s)
{
	int		fd;
	char	*line;

	fd = open("/tmp/.tmp.heredoc", O_CREAT | O_RDWR, S_IRWXU);
	line = NULL;
	while (!line || ft_strcmp(line, s) != 0)
	{
		line = readline(">");
		if (line && ft_strcmp(line, s) != 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
			line = NULL;
		}
	}
	free(line);
	return (fd);
}
