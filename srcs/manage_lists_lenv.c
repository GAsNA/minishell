/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lists_lenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:17:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/28 11:42:05 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lenv	*ft_create_elem_lenv(char *k, char *v)
{
	t_lenv	*elem;

	elem = malloc(sizeof(t_lenv));
	if (!elem)
		return (0);
	elem->k = k;
	elem->v = v;
	elem->next = NULL;
	return (elem);
}

void	ft_list_push_back_lenv(t_lenv **begin_list, char *k, char *v)
{
	t_lenv	*list;

	if (*begin_list)
	{
		list = *begin_list;
		while (list->next)
			list = list->next;
		list->next = ft_create_elem_lenv(k, v);
	}
	else
		*begin_list = ft_create_elem_lenv(k, v);
}

