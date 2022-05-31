/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:08:48 by rleseur           #+#    #+#             */
/*   Updated: 2022/05/31 13:27:33 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_create_elem_cmd(char **av)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd));
	if (!elem)
		return (0);
	elem->cmd = av;
	elem->fd_in = -42;
	elem->fd_out = -42;
	elem->pipe_fd[0] = -42;
	elem->pipe_fd[1] = -42;
	elem->pid = -42;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_cmd(t_cmd **begin_list, char **av)
{
	t_cmd	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_cmd(av);
	}
	else
		*begin_list = ft_create_elem_cmd(av);
}
