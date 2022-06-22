/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:59 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/22 18:37:01 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	write_in_file(char *line, t_lenv *lenv, int fd, int expand)
{
	int		i;
	int		j;
	int		n;
	int		inte;
	char	*new_line;

	j = 0;
	while (expand && there_are_expand(&line[j]))
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
		j = i - n - 1;
		if (j >= (int)ft_strlen(line) - 1)
			break ;
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
	close(fd2);
	return (1);
}

static int	check(char *line)
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

static void	check_quotes(char *s, int *expand)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\'' || s[i] == '"')
			*expand = 0;
}

int	make_heredoc(char *str, t_lenv *lenv)
{
	int		fd;
	int		fd2;
	int		expand;
	char	*line;
	char	*file;
	char	*s;

	file = "/tmp/.tmp.heredoc";
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	line = NULL;
	fd2 = dup(0);
	expand = 1;
	check_quotes(str, &expand);
	s = check_and_supp(str, 0);
	while (!line || ft_strcmp(line, s) != 0)
	{
		handle_signals_heredoc();
		line = readline(">");
		if (!check(line))
			break ;
		if (line && ft_strcmp(line, s) != 0)
		{
			write_in_file(line, lenv, fd, expand);
			line = NULL;
		}
	}
	free(s);
	if (!end_check(fd, fd2, line))
		return (-1);
	return (open(file, O_RDWR, 0666));
}
