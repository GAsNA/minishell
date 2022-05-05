/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:08:48 by rleseur           #+#    #+#             */
/*   Updated: 2022/05/05 11:51:42 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*ft_create_elem_pipe(char **av)
{
	t_cmd	*cmd;
	t_pipe	*elem;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->av = av;
	cmd->redir = NULL;
	elem = malloc(sizeof(t_pipe));
	if (!elem)
		return (0);
	elem->left = cmd;
	elem->right = NULL;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_pipe(t_pipe **begin_list, char **av)
{
	t_pipe	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_pipe(av);
	}
	else
		*begin_list = ft_create_elem_pipe(av);
}

static void	ft_list_clear_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->av[++i])
		free(cmd->av[i]);
	free(cmd->av);
	free(cmd);
}

void	ft_list_clear_pipe(t_pipe *begin_list)
{
	t_pipe	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		ft_list_clear_redir(begin_list->left->redir);
		ft_list_clear_cmd(begin_list->left);
		free(begin_list);
		begin_list = tmp;
	}
}
