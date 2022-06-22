/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists_regroup.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:07:42 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/20 21:41:09 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_regroup	*ft_create_elem_reg(char *str)
{
	t_regroup	*elem;

	elem = malloc(sizeof(t_regroup));
	if (!elem)
		return (0);
	elem->str = str;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_reg(t_regroup **begin_list, char *str)
{
	t_regroup	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_reg(str);
	}
	else
		*begin_list = ft_create_elem_reg(str);
}

void	ft_list_clear_reg(t_regroup *begin_list, int clear_str)
{
	t_regroup	*tmp;

	while (begin_list)
	{
		tmp = begin_list->next;
		if (clear_str)
			free(begin_list->str);
		free(begin_list);
		begin_list = tmp;
	}
}
