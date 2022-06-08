/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:08:48 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/08 13:43:44 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_create_elem_cmd(char **av, int fd_in)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd));
	if (!elem)
		return (0);
	elem->cmd = av;
	elem->fd_in = fd_in;
	elem->fd_out = -1;
	elem->pipe_fd[0] = -1;
	elem->pipe_fd[1] = -1;
	elem->pid = -1;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_cmd(t_cmd **begin_list, char **av, int fd_in)
{
	t_cmd	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_cmd(av, fd_in);
	}
	else
		*begin_list = ft_create_elem_cmd(av, fd_in);
}

void	ft_list_clear_cmd(t_cmd *begin_list)
{
	int		i;
	t_cmd	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		i = -1;
		if (begin_list->cmd)
		{
			while (begin_list->cmd[++i])
				free(begin_list->cmd[i]);
		}
		free(begin_list->cmd);
		free(begin_list);
		begin_list = tmp;
	}
}
