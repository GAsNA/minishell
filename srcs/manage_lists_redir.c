/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:09:50 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/27 14:46:28 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_create_elem_redir(char *str, enum e_type type)
{
	t_redir	*elem;

	elem = malloc(sizeof(t_redir));
	if (!elem)
		return (0);
	elem->val = str;
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_redir(t_redir **begin_list,
		char *str, enum e_type type)
{
	t_redir	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_redir(str, type);
	}
	else
		*begin_list = ft_create_elem_redir(str, type);
}

t_redir	*ft_create_elem_redir_null(void)
{
	t_redir	*elem;

	elem = malloc(sizeof(t_redir));
	if (!elem)
		return (0);
	elem->val = NULL;
	elem->next = NULL;
	return (elem);
}

void	ft_list_clear_redir(t_redir *begin_list)
{
	t_redir	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		free(begin_list);
		begin_list = tmp;
	}
}
