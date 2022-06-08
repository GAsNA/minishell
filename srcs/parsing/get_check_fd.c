/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_check_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 10:47:47 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/07 14:49:17 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	any_next_heredoc(t_regroup *reg)
{
	while (reg && ft_strcmp(reg->str, "|") != 0)
	{
		if (reg->next && ft_strcmp(reg->str, "<<") == 0 && reg->next)
			return (0);
		reg = reg->next;
	}
	return (1);
}

static int	get_fd_out(t_regroup *reg)
{
	int	flags;

	flags = -42;
	if (ft_strcmp(reg->str, ">") == 0)
		flags = O_CREAT | O_RDWR | O_TRUNC;
	else if (ft_strcmp(reg->str, ">>") == 0)
		flags = O_CREAT | O_APPEND;
	return (open(reg->next->str, flags, S_IRWXU));
}

static int	get_fd_in(t_regroup *reg)
{
	int	flags;

	flags = O_RDONLY;
	if (any_next_heredoc(reg))
		return (open(reg->next->str, flags));
	else
		return (-42);
}

void	check_fd_out(int *fd_in, int *fd_out, t_regroup *reg, char ***cmd)
{
	int	i;
	int	fd;

	fd = get_fd_out(reg);
	if (fd == -1)
	{
		printf("Rovidshell: %s: %s\n", reg->next->str, strerror(errno));
		i = -1;
		while ((*cmd)[++i])
			free((*cmd)[i]);
		free(*cmd);
		*cmd = NULL;
		*fd_in = -1;
	}
	else
		*fd_out = fd;
}

void	check_fd_in(int *fd_in, int *fd_out, t_regroup *reg, char ***cmd)
{
	int	i;
	int	fd;

	fd = get_fd_in(reg);
	if (fd == -1)
	{
		printf("Rovidshell: %s: %s\n", reg->next->str, strerror(errno));
		i = -1;
		while ((*cmd)[++i])
			free((*cmd)[i]);
		free(*cmd);
		*cmd = NULL;
		*fd_out = -1;
	}
	else if (fd != -42)
		*fd_in = fd;
}
