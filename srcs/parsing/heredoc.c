/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:59 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 11:31:01 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_n(char *line, int *i, int *inte)
{
	int	n;

	n = 0;
	while (line[++(*i)])
	{
		if ((line[(*i)] == '$' && line[(*i) + 1] && is_valid_iden(line[(*i) + 1]) && n == 0) || n > 0)
		{
			if ((!line[(*i)] || !is_valid_iden(line[(*i)])) && n > 0)
				break ;
			n++;
		}
		else if (line[(*i)] == '$' && line[(*i) + 1] == '?')
		{
			*inte = 1;
			break;
		}
	}
	return (n - 1);
}

int	make_heredoc(char *s, t_lenv *lenv)
{
	int		fd;
	int		n;
	int		i;
	int		j;
	int		inte;
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
			j = 0;
			while (there_are_expand(&line[j]))
			{
				inte = 0;
				i = -1;
				n = get_n(line, &i, &inte);
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
			line = NULL;
		}
	}
	free(line);
	close(fd);
	fd = open(file, O_RDWR, 0666);
	return (fd);
}
