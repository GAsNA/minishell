/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists_cmd2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:08:48 by rleseur           #+#    #+#             */
/*   Updated: 2022/05/30 13:58:00 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd2	*ft_create_elem_cmd2(char **av, int fd_out)
{
	t_cmd2	*elem;

	elem = malloc(sizeof(t_cmd2));
	if (!elem)
		return (0);
	elem->cmd = av;
	elem->fd_in = -42;
	elem->fd_out = fd_out;
	elem->pipe_fd[0] = -42;
	elem->pipe_fd[1] = -42;
	elem->pid = -42;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_cmd2(t_cmd2 **begin_list, char **av, int fd_out)
{
	t_cmd2	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_cmd2(av, fd_out);
	}
	else
		*begin_list = ft_create_elem_cmd2(av, fd_out);
}
