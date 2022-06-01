/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:31:59 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/01 16:18:38 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
int     ft_strcmp(char *s1, char *s2);
int	ft_strlen(char *s);
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
int	make_heredoc(void)
{
	int	fd;
	char	*line;

	fd = open(".tmp.heredoc", O_CREAT | O_RDWR, S_IRWXU);
	line = NULL;
	while (!line || ft_strcmp(line, "EOF") != 0)
	{
		line = readline(">");
		if (line && ft_strcmp(line, "EOF") != 0)
		{
			printf("%s\n", line);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
	}
	close(fd);
	return (fd);
}

int main()
{
	printf("fd: %i\n", make_heredoc());
	return (0);
}
