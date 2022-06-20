/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:59 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 11:44:17 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	make_heredoc(char *s, t_lenv *lenv)
{
	int		fd;
	char	*line;
	char	*file;

	file = "/tmp/.tmp.heredoc";
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	line = NULL;
	while (!line || ft_strcmp(line, s) != 0)
	{
		line = readline(">");
		if (line && ft_strcmp(line, s) != 0)
		{
			write_in_file(line, lenv, fd);
			line = NULL;
		}
	}
	free(line);
	close(fd);
	fd = open(file, O_RDWR, 0666);
	return (fd);
}
